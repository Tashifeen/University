# AICE1008 Mathematics II Coursework

## Summary
For this coursework, I investigated the SIR epidemic model and explored how numerical methods affect the accuracy of solutions. I first solved the SIR system using SciPy’s odeint and treated it as the reference solution. I then implemented Euler’s method and analysed how its accuracy changes with time resolution by computing peak and average error across different step sizes. This showed how coarse time steps lead to significant numerical deviation.

I extended the model by introducing a dynamic infection rate to simulate behavioural changes such as isolation or lockdowns. Using a fourth differential equation for β, I explored how different suppression rates affect peak infection and epidemic severity. I also implemented the Runge‑Kutta RK4 method as an extension and compared it with Euler and odeint, showing that RK4 provides a much more accurate approximation of the SIR system.

The report demonstrates practical skills in numerical ODE solving, error analysis, model extension, and interpreting epidemic behaviour through simulation.

## Files

### Source Files
- `task1_cw.ipynb` - Jupyter Notebook containing all coursework code, analysis, plots, and results
- `report.pdf` - Coursework report

## Features

### Part 1: SIR Model
- Implementation of the SIR epidemic model
- Numerical solution using `odeint`
- Numerical solution using Euler's Method
- Comparison of Euler and `odeint` solutions
- Peak error and average error analysis for different time steps

### Part 2: Epidemic Control
- Extension of the SIR model with a dynamic infection rate
- Investigation of suppression parameter η
- Analysis of infection peak reduction under behavioural changes
- Visualisation of epidemic curves for different values of η

### Extension: Runge–Kutta Method (RK4)
- Implementation of the fourth-order Runge–Kutta method
- Comparison of RK4 against Euler's Method
- Verification against the `odeint` reference solution
- Error analysis across different time resolutions

## Running

Open the notebook using Jupyter:

```bash
jupyter notebook task1_cw.ipynb
```

or

```bash
jupyter lab task1_cw.ipynb
```

Run all cells to reproduce the results and figures used in the report.

## Libraries Used

- NumPy
- SciPy
- Matplotlib
- Jupyter Notebook

## Output

The notebook produces:

- SIR population curves
- Euler error analysis plots
- Epidemic suppression model plots
- Peak infection analysis
- RK4 vs Euler comparison plots

## Notes

- Coursework investigates numerical solutions of epidemic models.
- `odeint` is used as the reference solution throughout the analysis.
- All figures included in the report are generated directly from the notebook.
