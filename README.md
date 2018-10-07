# Project description
**CityGen** is the interactive system for procedural city generation.

# TODO list (Main areas)
## Blueprints
We need a way to analyze existing cities for patterns. Knowing those patterns we can create some blueprints or rules which we'll use to generate new regions.

* Image recognition?
* Roads structure
* Lots and buildings blueprints

## Roads generation
Systems and algorithms that generate roads.

* Start with simple algorithm that will create square or rectangular lots
* Use heights maps
* Tensor fields tracing
* L-systems

## Lots subdivision
Creating areas to place buildings.

# Advanced areas
Some areas that will help the system to stand off.

## "Historic" development of a city
Defining separate city regions and classifying them by their "age" which previously developed systems didn't take into account. This may help to understand and categorize our blueprints.

# Implementation related stuff
List of general areas required for implementation.

* Start with 2D representation and then transition to 3D if needed
* IO system and file format
* Measurement units
* Blueprints catalogue (database)

## Referential materials
* [Game dev's blog](http://martindevans.me/tags/#procedural-generation-for-dummies-ref)
* [Procedural generation of parcels in urban modeling. Paper](https://www.cs.purdue.edu/cgvlab/papers/aliaga/eg2012.pdf)
* [Procedural modeling of cities. Paper](https://graphics.ethz.ch/Downloads/Publications/Papers/2001/p_Par01.pdf)
* [Interactive geometric simulation of 4D cities. Paper](https://graphics.ethz.ch/Downloads/Publications/Papers/2009/Web09/Web09.pdf)
* [A survey of procedural techniques for city generation. Paper](http://www.citygen.net/files/Procedural_City_Generation_Survey.pdf)
* [Interactive procedural street modeling. Paper](http://www.peterwonka.net/Publications/pdfs/2008.SG.Chen.InteractiveProceduralStreetModeling.pdf)
