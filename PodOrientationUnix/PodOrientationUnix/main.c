// Original David's code here: https://rloop.slack.com/files/piense/F2CSQ06V6/podorientation.zip

#include <stdio.h>
#include "LaserOrientation.h"

int main(int argc, const char * argv[]) {
    Laser1Reading = 8;
    Laser2Reading = 80;
    Laser3Reading = 79;
    RecalcOrientation();
    printf("HE1 Height: %f\n", HE1HeightAboveTrack);
    printf("HE2 Height: %f\n", HE2HeightAboveTrack);
    printf("HE3 Height: %f\n", HE3HeightAboveTrack);
    printf("HE4 Height: %f\n", HE4HeightAboveTrack);
    printf("Roll: %f\n", Roll);
    printf("Pitch: %f\n", Pitch);
    PrintPlane();
    return 0;
}
