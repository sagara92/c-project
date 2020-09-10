#include<stdio.h>
#include <math.h>
#define NUM_CELLS 1000



int main()
{
	double x, dx, xi, xf, E0, B0, k, ti, w, c, tf, dt, t;
	double E[NUM_CELLS], B[NUM_CELLS];
	E0 = 1.0;
	B0 = 1.0;
	xi = 0.0;
	t  = 0.0;
	xf = 1.0;
	c  = 1.0;
	ti = 0.0;
	tf = 10.0;/*10 second evolution*/
	k  = 2.0 * M_PI /(xf - xi);
	w  = k * c;
	dx = (xf - xi)/(NUM_CELLS - 1);
	dt = 0.01 * (dx / c);

	 /*Initial condition at t = 0*/
	
	for (int i = 0; i < NUM_CELLS; ++i)
	{
		x = xi + i*dx;
		E[i] = E0 * sin (k*x - w*t);
		B[i] = B0 * sin (k*x - w*t);
		//printf("The %d electric field component for xi = %f, is \t%f\n", i+1, x, E[i]);
		//printf("The %d magnetic field component for xi = %f, is \t%f\n", i+1, x, B[i]);
	}

	/*Time evolution of the field*/

	while(t < tf)
	{
		double dEdx[NUM_CELLS];
		double dBdx[NUM_CELLS];
		for (int i = 0; i < NUM_CELLS; ++i)
		{
			double Eminus = i > 0 			? E[i-1]:E[NUM_CELLS-2];
			double Eplus  = i < NUM_CELLS-1 ? E[i+1]:E[1];
			double Bminus = i > 0 			? B[i-1]:B[NUM_CELLS-2];
			double Bplus  = i < NUM_CELLS-1 ? B[i+1]:B[1];

			dEdx[i] = (Eplus-Eminus)/2.0 *dx;
			dBdx[i] = (Bplus-Bminus)/2.0 *dx;
		}
		for (int i = 0; i < NUM_CELLS; ++i)
		{
			E[i] -= c * dBdx[i] * dt;
			B[i] -= c * dEdx[i] * dt;
		}
		t += dt;
	}
	printf("Code ran well for %.2f second evolution\n", tf);
	// Output to a file
    // ------------------------------------------------------------------------
    FILE* outfile = fopen("em-wave-v3.dat", "w");

    for (int i = 0; i < NUM_CELLS; ++i)
    {
        double x = xi + i * dx;
        fprintf(outfile, "%f %f %f\n", x, E[i], B[i]);
    }
    fclose(outfile);
	return 0;
}