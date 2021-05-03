/**
    I copied and pasted the text for the header in main direclty from
    the project description.  However, the output in the body of the program
    use 10 character fields even though the header uses 11.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


    /**
    The flightTime function retuns the time the projectile
    is in the air.
    @param angle an integer value that represents the angle in degrees the
        projectile is fired
    @param v0 the intial velocity of the projectile as a double in m/s
    @return the time in seconds the projectile is in the air as a double.
    */
    double flightTime( int angle, double v0 )
    {
        double timeInAir = 0.0;
        double vY = sin(angle * M_PI / 180);//acceleration is only in the y direction
        vY = v0 * vY; 
        timeInAir = vY / (9.81 / 2.0);//flight time
        return timeInAir;
    }

    /**
    The tableRow function prints a formatted row of calculated output based on the
    user's input of V0.
    @param angle the angle in degrees the projectile is fired wrt the horizontal plane
    @param v0 the intial velocity of the projectile in m/s
    @param t the flight time of the projectile in s
    */
    void tableRow( int angle, double v0, double t )
    {
        t = flightTime( angle, v0 );
        double dx = (2.0 * v0 * v0 * cos(angle * M_PI / 180) * sin(angle * M_PI / 180)) / (9.81);//dy = 0 when t = 2v0sin(theta)/g
        printf( "%10d |", angle); printf(" %10.3lf |", v0); printf(" %10.3lf | ", t); printf("%10.3lf", dx);
    }

    /**
    The main function doens not accept any command line arguments.
    User input for the intial velocity is consumed and a header is then
    printed with formatted rows of calculated data.
    */
    int main()
    {
        int angle = 0;
        double v0;
        printf("V0: ");
        scanf("%lf", &v0);
        printf("%c", '\n');
        printf("     angle |         v0 |       time |   distance\n");
        printf("-----------+------------+------------+-----------\n");
        while (angle <= 90) {
            tableRow(angle, v0, 0); printf("%c", '\n');
            angle += 5;
        }
        return 0;
    }
