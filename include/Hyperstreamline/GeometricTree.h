#ifndef CITYGEN_GEOMETRIC_TREE_H
#define CITYGEN_GEOMETRIC_TREE_H

#include "GenericTypes.h"
#include <vector>
#include <algorithm>

namespace CityGen
{
namespace Utils
{
template<class TItem, class TVector, class TBounds>
class GeometricTree
{
public:
  GeometricTree(const TBounds &bounds, std::size_t threshold, std::size_t maxDepth)
    : _threshold(threshold), _root(*this, bounds, 0, maxDepth) {}

  void insert(const TBounds &bounds, const TItem &item)
  {
    _root.insert({ bounds, item }, _threshold);
    ++_count;
  }

  bool remove(const TBounds &bounds, const TItem &item)
  {
    const std::size_t itemsRemoved = _root.remove(bounds, item);

    _count -= itemsRemoved;
    return itemsRemoved > 0;
  }

  template<class T>
  bool removeIf(const TBounds &bounds, T &&predicate)
  {
    const std::size_t itemsRemoved = _root.removeIf(bounds, predicate);

    _count -= itemsRemoved;
    return itemsRemoved > 0;
  }

  void clear()
  {
    _root.clear();
    _count = 0;
  }

  std::size_t getItemsCount() const { return _count; }

  std::vector<TItem> getItemsIntersectWithBounds(const TBounds &bounds) const
  {
    std::vector<TItem> items;
    const auto rootItems = _root.intersects(bounds);

    std::transform(std::begin(rootItems), std::end(rootItems), std::back_inserter(items),
    [](const auto &member) { return std::move(member.item); });

    return items;
  }

  std::vector<TItem> getItemsInBounds(const TBounds &bounds) const
  {
    std::vector<TItem> retItems;
    auto items = _root.intersects(bounds);

    for (auto &member : items)
    {
      if (contains(bounds, member.bounds))
      {
        retItems.push_back(std::move(member.item));
      }
    }

    return retItems;
  }

protected:
  struct Member
  {
    TBounds bounds;
    TItem item;
  };

  class Node
  {
  public:
    Node(const GeometricTree<TItem, TVector, TBounds> &tree, const TBounds &bounds, std::size_t depth,
      std::size_t maxDepth)
      : _tree(tree), _bounds(bounds), _depth(depth), _maxDeth(maxDepth) {}

    void insert(const Member &member, std::size_t splitThreshold)
    {
      if (_children.empty())
      {
        _items.push_back(member);

        if (_items.size() > splitThreshold && _depth < _maxDeth)
        {
          split(splitThreshold);
        }
      }
      else
      {
        for (auto &child : _children)
        {
          if (_tree.contains(child.getBounds(), member.bounds))
          {
            child.insert(member, splitThreshold);
            return;
          }
        }
      }
    }

    std::size_t remove(const TBounds &bounds, const TItem &item)
    {
      return removeRecursively(bounds, [item](const Member &m) { return m.item == item; }, true);
    }

    template<class T>
    std::size_t removeIf(const TBounds &bounds, T &&predicate)
    {
      return removeRecursively(bounds, [predicate](const Member &m) { return predicate(m.item); }, false);
    }

    std::vector<Member> intersects(const TBounds &bounds) const
    {
      std::vector<Member> items;

      if (_tree.intersects(_bounds, bounds))
      {
        std::copy_if(std::begin(_items), std::end(_items), std::back_inserter(items),
        [this, &bounds](const auto &item)
        {
          return _tree.intersects(item.bounds, bounds);
        });

        for (const auto &child : _children)
        {
          auto childItems = child.intersects(bounds);

          std::move(std::begin(childItems), std::end(childItems), std::back_inserter(items));
        }
      }

      return items;
    }

    void clear()
    {
      _items.clear();
      _children.clear();
    }

    const TBounds &getBounds() const { return _bounds; }
    const std::vector<Member> &getItems() const { return _items; }
    const std::vector<Node> &getChildren() const { return _children; }

  private:
    void split(std::size_t splitThreshold)
    {
      const auto bounds = _tree.split(_bounds);

      std::transform(std::begin(bounds), std::end(bounds), std::back_inserter(_children),
      [this](const auto &bounds)
      {
        return Node{ _tree, bounds, _depth + 1, _maxDeth };
      });
      
      _items.erase(std::remove_if(std::begin(_items), std::end(_items),
      [this, splitThreshold](const auto &item)
      {
        const auto it = std::find_if(std::begin(_children), std::end(_children),
        [this, &item](const auto &child)
        {
          return _tree.contains(child.getBounds(), item.bounds);
        });
        const bool moveToChild = it != std::end(_children);

        if (moveToChild)
        {
          it->insert(item, splitThreshold);
        }

        return moveToChild;
      }), std::end(_items));
    }

    template<class T>
    std::size_t removeRecursively(const TBounds &bounds, T &&predicate, bool removeSingleItem)
    {
      std::size_t itemsRemoved = 0;

      if (!_tree.intersects(_bounds, bounds) && &(_tree._root) != this)
      {
        return itemsRemoved;
      }

      if (removeSingleItem)
      {
        const auto it = std::find_if(std::begin(_items), std::end(_items), predicate);

        if (it != std::end(_items))
        {
          _items.erase(it);
          itemsRemoved = 1;
        }
      }
      else
      {
        const std::size_t count = _items.size();

        _items.erase(std::remove_if(std::begin(_items), std::end(_items), predicate), std::end(_items));

        itemsRemoved = _items.size() - count;
      }

      for (auto &child : _children)
      {
        const std::size_t removedFromChild = child.removeRecursively(bounds, predicate, removeSingleItem);

        itemsRemoved += removedFromChild;

        if (removedFromChild > 0 && removeSingleItem)
        {
          break;
        }
      }

      return itemsRemoved;
    }

    std::vector<Member> _items;
    std::vector<Node> _children;

    const GeometricTree<TItem, TVector, TBounds> &_tree;
    const TBounds _bounds;
    const std::size_t _depth;
    const std::size_t _maxDeth;
  };
  
  virtual bool contains(const TBounds &container, const TBounds &contained) const = 0;
  virtual bool intersects(const TBounds &a, const TBounds &b) const = 0;
  virtual std::vector<TBounds> split(const TBounds &bounds) const = 0;

  std::size_t _count = 0;

private:
  const std::size_t _threshold = 0;

  Node _root;
};

template<class T>
class QuadTree : public GeometricTree<T, Vector, Rect>
{
public:
  using ItemType = T;
  using VectorType = Vector;
  using BoundsType = Rect;
  using GeometricTree<ItemType, VectorType, BoundsType>::GeometricTree;

protected:
  bool contains(const BoundsType &container, const BoundsType &contained) const override
  {
    return container.contains(contained);
  }

  bool intersects(const BoundsType &a, const BoundsType &b) const override
  {
    return a.intersects(b);
  }

  std::vector<BoundsType> split(const BoundsType &bounds) const override
  {
    std::vector<BoundsType> newBounds;
    const Vector size = (bounds.bottomRight - bounds.topLeft) / 2.f;

    for (std::size_t x = 0; x < 2; ++x)
    {
      for (std::size_t y = 0; y < 2; ++y)
      {
        const Vector offset = size * Vector{ static_cast<float>(x), static_cast<float>(y) };

        newBounds.emplace_back(bounds.topLeft + offset, bounds.topLeft + size + offset);
      }
    }

    return newBounds;
  }
};
}
}

#endif
