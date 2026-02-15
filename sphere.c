#include <stdio.h>
#include <math.h> // for pow()

typedef struct {
    double x, y, z;   // centre
    double r;         // radius
} Sphere;

int spheres_do_not_overlap(const Sphere *list, int count)
{
	for (int i = 0; i < count; i++) {
		for (int j = i + 1; j < count; j++) {

			double dx = list[i].x - list[j].x;
			double dy = list[i].y - list[j].y;
			double dz = list[i].z - list[j].z;

			double dist2 = dx*dx + dy*dy + dz*dz;
            double rad  = list[i].r + list[j].r;
            double rad2 = rad * rad;

            if (dist2 < rad2) {
                return 0;   // at least one overlap
            }
        }
    }
    return 1; // none overlap
}



int main(void) {
    Sphere test1[] = {
        {0, 0, 0, 1},
        {5, 0, 0, 1},
        {0, 5, 0, 2}
    };

    Sphere test2[] = {
        {0, 0, 0, 2},
        {3, 0, 0, 2},
        {0, 10, 0, 1}
    };

    Sphere test3[] = {
        {0, 0, 0, 1},
        {2, 0, 0, 1}
    };

    Sphere test4[] = {
        {0, 0, 0, 3},
        {2, 2, 2, 3}
    };

    printf("Test1 (no overlap): %d\n", spheres_do_not_overlap(test1, 3));
    printf("Test2 (overlap): %d\n", spheres_do_not_overlap(test2, 3));
    printf("Test3 (touching): %d\n", spheres_do_not_overlap(test3, 2));
    printf("Test4 (3D overlap): %d\n", spheres_do_not_overlap(test4, 2));

    return 0;
}
