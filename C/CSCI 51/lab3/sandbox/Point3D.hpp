struct Point3D
{
   int x, y, z;
   Point3D()
   { //default constructor
      x = 0;
      y = 0;
      z = 0;
   }
   Point3D(int x, int y, int z)
   {
      this->x = x;
      this->y = y;
      this->z = z;
   }
};