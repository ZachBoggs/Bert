#include "raylib.h"
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;

constexpr int screenWidth = 1200;
constexpr int screenHeight = 750;

void rotateX3d(const float& angle, vector<Vector3>& points)
{
  for(int i=0;i<points.size();++i)
  {
    float newX = points[i].x;
    float newY = (points[i].y * cos(angle)) - (sin(angle) * points[i].z);
    float newZ = (points[i].y * sin(angle)) + (cos(angle) * points[i].z);

    points[i].x = newX;
    points[i].y = newY;
    points[i].z = newZ;
  }
}

void rotateY3d(const float& angle, vector<Vector3>& points)
{
  for(int i=0;i<points.size();++i)
  {
    float newX = (points[i].x * cos(angle)) + (points[i].z * sin(angle));
    float newY = points[i].y;
    float newZ = (points[i].x * (-1 * sin(angle))) + (points[i].z * cos(angle));

    points[i].x = newX;
    points[i].y = newY;
    points[i].z = newZ;
  }
}

void rotateZ3d(const float& angle, vector<Vector3>& points)
{
  for(int i=0;i<points.size();++i)
  {
    float newX = (points[i].x * cos(angle)) + (points[i].y * ( -1 * sin(angle)));
    float newY = (points[i].x * sin(angle)) + (points[i].y * cos(angle));
    float newZ = points[i].z;

    points[i].x = newX;
    points[i].y = newY;
    points[i].z = newZ;
  }
}

void rotateX(const float& angle, vector<Vector2>& points)
{
  for(int i=0;i<points.size();++i)
  {
    float newX = (points[i].x * cos(angle)) - (points[i].y * sin(angle));
    float newY = (points[i].x * sin(angle)) + (points[i].y * cos(angle));
    points[i].x = newX;
    points[i].y = newY;
  }
}

void rotateX(const float& angle, vector<Vector3>& points)
{
  for(int i=0;i<points.size();++i)
  {
    float newX = (points[i].x * cos(angle)) - (points[i].y * sin(angle));
    float newY = (points[i].x * sin(angle)) + (points[i].y * cos(angle));
    points[i].x = newX;
    points[i].y = newY;
  }
}


class laser
{
  Vector2 originPoint;
  Vector2 scaleFactor;
  float acceleration;

  // points on the laser
  Vector2 backEnd;
  Vector2 frontEnd;
  float direction;
  bool leftToRight;

  public:

  laser(const Vector2& origin,const Vector2& target) : 
    acceleration(0.04f),
    originPoint(origin),
    scaleFactor(Vector2{target.x - origin.x,target.y - origin.y}),
    backEnd(origin),
    frontEnd(Vector2{origin.x + scaleFactor.x * 0.40f,origin.y + scaleFactor.y * 0.40f})
  {
  }

  bool timeToDestroy()
  {
    // checking if the laser is out of bounds, if so then we return true
    if(backEnd.x  > screenWidth  || backEnd.x  <= 0) { return true; }
    if(backEnd.y  > screenHeight || backEnd.y  <= 0) { return true; }
    return false;
  }

  void updatePosition()
  {
    acceleration += 0.01f,

    backEnd.x += acceleration * scaleFactor.x;
    backEnd.y += acceleration * scaleFactor.y;

    frontEnd.x += acceleration * scaleFactor.x;
    frontEnd.y += acceleration * scaleFactor.y;
  }

  void drawLaser()
  {
    DrawLineV(backEnd,frontEnd,RED);
  }
};


int main() 
{

  InitWindow(screenWidth, screenHeight, "Rotation Matrix");
  SetTargetFPS(60);

  float currentRotation = 0.1f;
  vector<Vector3> points =
  {
    Vector3{-0.5f,-0.5f,-0.5f},
    Vector3{-0.5f, 0.5f,-0.5f},
    Vector3{-0.5f,-0.5f, 0.5f},
    Vector3{-0.5f, 0.5f, 0.5f},
    Vector3{ 0.5f,-0.5f,-0.5f},
    Vector3{ 0.5f, 0.5f,-0.5f},
    Vector3{ 0.5f,-0.5f, 0.5f},
    Vector3{ 0.5f, 0.5f, 0.5f}
  };

  vector<Vector3> smilePointsBase =
  {
    Vector3{ 0.2f,-0.2f, 0.5f},
    Vector3{-0.2f,-0.2f, 0.5f}
  };

  for(int i=0;i<smilePointsBase.size();++i)
  {
    smilePointsBase[i].x *= 300;
    smilePointsBase[i].y *= 300;
    smilePointsBase[i].z *= 300;
  }

  vector<Vector3> smallShape =
  {
    Vector3{-0.5f,-0.5f,-0.5f},
    Vector3{-0.5f, 0.5f,-0.5f},
    Vector3{-0.5f,-0.5f, 0.5f},
    Vector3{-0.5f, 0.5f, 0.5f},
    Vector3{ 0.5f,-0.5f,-0.5f},
    Vector3{ 0.5f, 0.5f,-0.5f},
    Vector3{ 0.5f,-0.5f, 0.5f},
    Vector3{ 0.5f, 0.5f, 0.5f}
  };

  // scaling the shape
  for(int i=0;i<smallShape.size();++i)
  {
    smallShape[i].x *= 100;
    smallShape[i].y *= 100;
    smallShape[i].z *= 100;
  }

  // scaling the cube
  for(int i=0;i<points.size();++i)
  {
    points[i].x *= 300;
    points[i].y *= 300;
    points[i].z *= 300;
  }

    
  vector<Vector3> copyPoints = points;
  vector<Vector3> smilePoints = smilePointsBase;
  float angleRate      = 0.20f;
  float smallShapeRate = 0.20f;
  float eyeSize = 42.0f;

  vector<laser> laserHolder;

  while (!WindowShouldClose()) 
  {
    // updating and erasing lasers
    for(int i=0;i<laserHolder.size();++i)
    {
      // if the laser is out of bounds and should be destroyed
      if(laserHolder[i].timeToDestroy())
      {
        laser frontLaser = laserHolder[0];
        laserHolder[0] = laserHolder[i];
        laserHolder[i] = frontLaser;

        laserHolder.erase(laserHolder.begin());
        i--;
        continue;
      }
      laserHolder[i].updatePosition();
    }


    smilePoints = smilePointsBase;
    points = copyPoints;
    if(smallShapeRate > 0.20f) { smallShapeRate -= 0.1f; }
    if(smallShapeRate < 0.2f)  { smallShapeRate  = 0.2f; }

    Vector2 currentMousePos = GetMousePosition();

    // rotating the cube
    rotateX3d(((currentMousePos.y / (screenHeight /2)) - 1.0f) * angleRate * -1, points     );
    rotateY3d(((currentMousePos.x / (screenWidth  /2)) - 1.0f) * angleRate     , points     );

    // rotating the front of the face
    rotateX3d(((currentMousePos.y / (screenHeight /2)) - 1.0f) * angleRate * -1, smilePoints);
    rotateY3d(((currentMousePos.x / (screenWidth  /2)) - 1.0f) * angleRate     , smilePoints);


    // rotating the small cube based on time and if the cube is being shaken
    rotateX3d(0.06f * smallShapeRate * cos((smallShapeRate/0.2f) * PI / 2), smallShape);
    rotateY3d(0.01f * smallShapeRate * sin((smallShapeRate/0.2f) * PI / 2),smallShape);
    rotateZ3d(0.03f * smallShapeRate * sin((smallShapeRate/0.2f) * PI / 2),smallShape);

       
    // starting drawing
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0,0,screenWidth,screenHeight,Color{255,0,0,10 * (smallShapeRate - 0.2f)});
    
    

    string nameText = "Bert";
    DrawText(nameText.c_str(),screenWidth/2 - MeasureText(nameText.c_str(),50)/2,40,50,BLACK);

    // drawing the corners to the cube
    for(int i=0;i<points.size();++i)
    {
      DrawCircle(points[i].x + screenWidth/2,points[i].y + screenHeight/2,3.0f,RED);

      // drawing lines from this corner to the other corners
      for(int j=0;j<points.size();++j)
      {
        DrawLine(points[j].x + screenWidth/2,points[j].y + screenHeight/2,points[(i + 1) % points.size()].x + screenWidth/2,points[(i + 1) % points.size()].y + screenHeight/2,BLACK);
      }
    }

    if(IsKeyPressed(KEY_SPACE) || (smallShapeRate <= 3.2f && IsKeyDown(KEY_SPACE)))
    { 
      smallShapeRate = 4.0f; 
    }

    for(int i=0;i<smilePoints.size();++i)
    {
      // calculating our key variables that we will use
      float circleX = smilePoints[i].x + screenWidth/2;
      float circleY = smilePoints[i].y + screenHeight/2;
      float distanceFromEye = sqrtf(pow(circleX - currentMousePos.x,2) + pow(circleY - currentMousePos.y,2));
      float pupilX = circleX + (20 * ((currentMousePos.x / circleX) - 1.0f)) + (5 * cos((smallShapeRate / 0.2f)));
      float pupilY = circleY + (20 * ((currentMousePos.y / circleY) - 1.0f)) + (5 * sin((smallShapeRate / 0.2f)));

      float mouseDistanceX = currentMousePos.x - pupilX;
      float mouseDistanceY = currentMousePos.y - pupilY;

      // drawing the current eye with an outline
      DrawCircle(circleX,circleY,eyeSize,GRAY);
      DrawCircle(circleX,circleY,eyeSize - 2.0f,WHITE);
      DrawCircle
      (
        pupilX,
        pupilY,
        
        (eyeSize - 5.0f) - (0.04f * distanceFromEye),
        BLACK
      );

      float eyebrowOffset = 0.0f;
      if(IsKeyDown(KEY_SPACE))
      {
        eyebrowOffset = 9.0f;
      }


      //// making an eyebrow for each eye and setting the angle of it based on distance from the cursor
      //
      Rectangle eyebrow{circleX-30.0f,circleY-(115.0f - eyebrowOffset) + (10 * (7 - (distanceFromEye/100.0f))),60.0f,10.0f};
      eyebrow.x += (eyebrow.width/2);
      eyebrow.y += (eyebrow.height/2);
      Vector2 eyebrowOrigin{(eyebrow.width/2),(eyebrow.height/2)};

      const float rangeThreshold  = 200.0f;
      const float transitionRange = 100.0f;  // pixels over which we blend (200 -> 300)
      
      float angleNear = 80.0f * (mouseDistanceX / (screenWidth * 0.5f));
      float angleFar  = 40.0f * (mouseDistanceX / (float)screenWidth);
      
      // how far past the threshold are we, normalized 0..1
      float t = (distanceFromEye - rangeThreshold) / transitionRange;
      if (t < 0.0f) t = 0.0f;
      if (t > 1.0f) t = 1.0f;
      
      // linear interpolation between the two angles
      float angle = angleNear + (angleFar - angleNear) * t + (IsKeyDown(KEY_SPACE) * (20.0f * (i == 0 ? -1 : 1)));
      
      DrawRectanglePro(eyebrow, eyebrowOrigin, angle, BLACK);
      //
      ////


      if(IsKeyDown(KEY_SPACE))
      {
        // calculating the pupil position
        Vector2 pupilLocation
        {
          pupilX,
          pupilY
        };


        //// getting the normalized direction from the pupil to the mouse
        //
        Vector2 laserDirection
        {
          currentMousePos.x - pupilLocation.x,
          currentMousePos.y - pupilLocation.y
        };

        float currentLength = sqrt((laserDirection.x * laserDirection.x) + (laserDirection.y * laserDirection.y));

        laserDirection.x /= currentLength;
        laserDirection.y /= currentLength;
        //
        ////


        float laserLength = 50 + abs(cos(smallShapeRate) * 40);

        Vector2 laserPoint{(laserDirection.x * laserLength) + pupilLocation.x, (laserDirection.y * laserLength) + pupilLocation.y};

        // pushing back a laser for both eyes
        laserHolder.push_back
        (
          laser
          (
            pupilLocation,
            laserPoint
          )
        );
      }
    }


    // drawing lines from the cube to the small cube
    for(int i=0;i<points.size();++i)
    {
      DrawLine(points[i].x + screenWidth/2,points[i].y + screenHeight/2,smallShape[i].x + currentMousePos.x,smallShape[i].y + currentMousePos.y,RED);
    }

    // drawing the eyes
    for(int i=0;i<smallShape.size();++i)
    {
      DrawCircle(smallShape[i].x + currentMousePos.x,smallShape[i].y + currentMousePos.y,3.0f,RED);
      for(int j=0;j<smallShape.size();++j)
      {
        DrawLine(smallShape[j].x + currentMousePos.x,smallShape[j].y + currentMousePos.y,smallShape[(i + 1) % smallShape.size()].x + currentMousePos.x,smallShape[(i + 1) % smallShape.size()].y + currentMousePos.y,BLACK);

      }
    }

    // drawing our lasers
    for(int i=0;i<laserHolder.size();++i)
    {
      laserHolder[i].drawLaser();
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
