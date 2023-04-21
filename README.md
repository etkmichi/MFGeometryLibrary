# MFGeometryLibrary
Library for creating some geometrical objects and their physics representation of bulletPhysics.
Base geometries can be found in the dir [MFBaseGeometries](https://github.com/etkmichi/MFGeometryLibrary/tree/main/MFGeometryLibrary/MFBaseGeometries)


To build the library (For a release build, replace "Debug" with "Release" in the last line):
```
   git clone https://github.com/etkmichi/MFGeometryLibrary.git
   cd MFGeometryLibrary
   chmod +x build_script.sh
   ./build_script.sh Debug
```
The MFNoiseGeometry can be used to create more complex surfaces. The related physics object is not convex and may use a lot of process time. A better implementation would be to map noise values onto a box. The box is a convex physics shape and will result in less physics glitches. The mapped noise points can be scaled for better performance.

The compund geometry classes can be used to stick some geometries together (including the physical representations).


Additional libraries:<br>
  * [MFBasics](https://github.com/etkmichi/MFBasics)
  * bulletPhysics
    * LiearMath
    * BulletDynamics
    * BulletSoftBody
    * Bullet3Collision
    * BulletCollision
    * Bullet3Common
    * Bullet3Dynamics
    * Bullet3Geometry
  * libnoise/noise
