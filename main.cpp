/// https://developers.google.com/streetview/spherical-metadata
#include "photosphere.h"
#include "utilities.h"


int main(int argc, char **argv)
{
    PhotoSphere *ps = PhotoSphere::FromFile("../assets/PhotoSphereTestImage.jpg");

    return 0;
}

