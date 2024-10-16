**Interest Rate Curve Construction**

**Introduction**

This project came from the need to demonstrate my ability to code in C++ and how IR and FX Curve Construction works to potential employees. I had to put this together quickly, so I have put more weight on getting the curve-solving to work versus the best
coding choices. The current implementation (as of 12-10-2024) is at a very basic stage, solving for the OIS curve only but all the code architecture is there for the expansion into the full multi-curve curve construction and FX curve solving. Coding Practice, Design decisions or other features I would of done differently are listed at the bottom in the **Improvements** section. 

**Project Design**

From a high-level the Curve Construction works from the construction of three user-defined objects:

- **CurveSet** - This class contains the vector of **Curve** classes which will be used to create a rates mapping which is necessary to price the input market instruments. The rates mapping is a map of functors that will return either forward rates or discount factors,
depending on the curve model. 
- **InstrumentSet** - This class will hold a vector of **InstrumentPricer** classes which are used in conjunction with the curveset rates mapping tp price the linear instruments used in the curve construction problem.
- **Solver** - This class holds reference to the above two objects and uses a multivariate LM algorithm to find curve knot points that price the input instruments at par.

If you refer to the **Testing** project you can see Unit test cases written explaining the construction of these objects, ultimately showing how the curve solve works. 

**User Instructions**

The code was written using visual studio 2022, ideally I would of made a CMake file but time was not sufficient. I haven't used any external packages so you should be able to download the full code base and assuming you use VS 2022, the code should run.

**Improvements**
In this section I list initial list of improvements, I am sure there are many more to be added. 
**High Priority** 
- Add in Central Banking Meeting Dates and Step interpolation in the front end of the base curve.
- Put all Calendars to the heap
- Add in remaining IR InstrumentPricers: OISBasis Swaps, CB Swaps, Cash etc.
- Add Instrument Filtering Rules and Logic

**Low Priority**
- Add in FX Instrument pricers: FX Forwards and XCCY Swaps.
- Look into the need for the use of IR and FX turns (synthetic instruments).
- Add in Automatic Adjoint Differentiation (AAD).
- Add in move constructors for the Curves and InstrumentPricers, so that unique pointers can be used instead of shared pointers.
- Add serialisation

**Contact Details**
petenallen4321@gmail.com
