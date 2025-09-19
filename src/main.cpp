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


class lazer
{
  Vector2 originPoint;
  Vector2 scaleFactor;
  float acceleration;

  // points on the lazer
  Vector2 backEnd;
  Vector2 frontEnd;
  float direction;
  bool leftToRight;

  public:

  lazer(const Vector2& origin,const Vector2& target) : 
    acceleration(0.04f),
    originPoint(origin),
    scaleFactor(Vector2{target.x - origin.x,target.y - origin.y}),
    //scaleFactor(Vector2{((target.x / origin.x) -0.5f) * 10,((target.y / origin.y) - 0.5f) * 10}),
    //scaleFactor(Vector2{(target.x - origin.x),(target.y - origin.y)}),
    //scaleFactor(Vector2{(target.x - origin.x) / sqrt((target.x - origin.x) + (target.y - origin.y)), (target.y - origin.y) / sqrt(pow((target.x - origin.x),2) + pow((target.y - origin.y),2))}),
    backEnd(origin),
    frontEnd(Vector2{origin.x + scaleFactor.x * 0.40f,origin.y + scaleFactor.y * 0.40f})
    //frontEnd(Vector2{origin.x + scaleFactor.x * 4.0f,origin.y + scaleFactor.y * 4.0f})
  {
  }

  bool timeToDestroy()
  {
    // checking if the lazer is out of bounds, if so then we return true
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

  void drawLazer()
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

    /*
    Vector3{ 0.0f, 0.0f, 0.0f},

    Vector3{ 0.0f, 0.0f, 0.5f},
    Vector3{ 0.0f, 0.5f, 0.0f},
    Vector3{ 0.5f, 0.0f, 0.0f},
    Vector3{ 0.0f, 0.0f,-0.5f},
    Vector3{ 0.0f,-0.5f, 0.0f},
    Vector3{-0.5f, 0.0f, 0.0f}
    */

    /*
    Vector3{-0.5f,-0.5f, 0.0f},
    Vector3{ 0.5f,-0.5f, 0.0f},
    Vector3{ 0.5f, 0.5f, 0.0f},
    Vector3{-0.5f, 0.5f, 0.0f},
    Vector3{ 0.0f, 0.5f, 0.0f},
    Vector3{ 0.0f,-0.5f, 0.0f},
    Vector3{-0.5f, 0.0f, 0.0f},
    Vector3{ 0.5f, 0.0f, 0.0f}
    */
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

  for(int i=0;i<smallShape.size();++i)
  {
    smallShape[i].x *= 100;
    smallShape[i].y *= 100;
    smallShape[i].z *= 100;
  }


  for(int i=0;i<points.size();++i)
  {
    points[i].x *= 300;
    points[i].y *= 300;
    points[i].z *= 300;
  }

    //rotateX3d(PI / 4, points);

  /*
    rotateX(PI/4,points);
    rotateX3d(PI / 4, points);
    */
    
  vector<Vector3> copyPoints = points;
  vector<Vector3> smilePoints = smilePointsBase;
  float angleRate      = 0.20f;
  float smallShapeRate = 0.20f;
  float eyeSize = 42.0f;

  vector<lazer> lazerHolder;

  while (!WindowShouldClose()) 
  {

    // updating and erasing lazers
    for(int i=0;i<lazerHolder.size();++i)
    {
      if(lazerHolder[i].timeToDestroy())
      {
        lazer frontLazer = lazerHolder[0];
        lazerHolder[0] = lazerHolder[i];
        lazerHolder[i] = frontLazer;

        lazerHolder.erase(lazerHolder.begin());
        i--;
        continue;
      }
      lazerHolder[i].updatePosition();
    }


    smilePoints = smilePointsBase;
    points = copyPoints;
    if(smallShapeRate > 0.20f) { smallShapeRate -= 0.1f; }
    if(smallShapeRate < 0.2f)  { smallShapeRate  = 0.2f; }

    Vector2 currentMousePos = GetMousePosition();

    rotateX3d(((currentMousePos.y / (screenHeight /2)) - 1.0f) * angleRate * -1, points     );
    rotateY3d(((currentMousePos.x / (screenWidth  /2)) - 1.0f) * angleRate     , points     );

    rotateX3d(((currentMousePos.y / (screenHeight /2)) - 1.0f) * angleRate * -1, smilePoints);
    rotateY3d(((currentMousePos.x / (screenWidth  /2)) - 1.0f) * angleRate     , smilePoints);

    //rotateY3d(() * angleRate, points);
    //rotateZ3d(0.03f * angleRate, points);

    rotateX3d(0.06f * smallShapeRate * cos((smallShapeRate/0.2f) * PI / 2), smallShape);
    rotateY3d(0.01f * smallShapeRate * sin((smallShapeRate/0.2f) * PI / 2),smallShape);
    rotateZ3d(0.03f * smallShapeRate * sin((smallShapeRate/0.2f) * PI / 2),smallShape);

    /*
    rotateX3d(0.06f * smallShapeRate, smallShape);
    rotateY3d(0.01f * smallShapeRate,smallShape);
    rotateZ3d(0.03f * smallShapeRate,smallShape);
    */

       
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawRectangle(0,0,screenWidth,screenHeight,Color{255,0,0,10 * (smallShapeRate - 0.2f)});
    
    

    string nameText = "Bert";
    DrawText(nameText.c_str(),screenWidth/2 - MeasureText(nameText.c_str(),50)/2,40,50,BLACK);

    for(int i=0;i<points.size();++i)
    {
      DrawCircle(points[i].x + screenWidth/2,points[i].y + screenHeight/2,3.0f,RED);
      

      for(int j=0;j<points.size();++j)
      {
        //DrawLine(points[j].x + screenWidth/2,points[j].y + screenHeight/2,points[(i + 1) % points.size()].x + screenWidth/2,points[(i + 1) % points.size()].y + screenHeight/2,Color{0,i * ((1.0f/(float)points.size()) * 255.0f),255,255});
        DrawLine(points[j].x + screenWidth/2,points[j].y + screenHeight/2,points[(i + 1) % points.size()].x + screenWidth/2,points[(i + 1) % points.size()].y + screenHeight/2,BLACK);
      }
    }

    if(IsKeyPressed(KEY_SPACE) || (smallShapeRate <= 3.2f && IsKeyDown(KEY_SPACE)))
    { 
      smallShapeRate = 4.0f; 
    }

    for(int i=0;i<smilePoints.size();++i)
    {

      float circleX = smilePoints[i].x + screenWidth/2;
      float circleY = smilePoints[i].y + screenHeight/2;
      float distanceFromEye = sqrtf(pow(circleX - currentMousePos.x,2) + pow(circleY - currentMousePos.y,2));
      float pupilX = circleX + (20 * ((currentMousePos.x / circleX) - 1.0f)) + (5 * cos((smallShapeRate / 0.2f)));
      float pupilY = circleY + (20 * ((currentMousePos.y / circleY) - 1.0f)) + (5 * sin((smallShapeRate / 0.2f)));

      DrawCircle(circleX,circleY,eyeSize,GRAY);
      DrawCircle(circleX,circleY,eyeSize - 2.0f,WHITE);
      DrawCircle
      (
        pupilX,
        pupilY,
        //(cos((smallShapeRate/0.2f) * PI / 2) * 2) + (eyeSize - 5.0f) - 0.04f * sqrtf(pow((screenWidth/2 - currentMousePos.x),2) + pow((screenHeight/2) - currentMousePos.y,2)),
        (eyeSize - 5.0f) - (0.04f * distanceFromEye),
        //(eyeSize - 5.0f) - 0.04f * sqrtf(pow((screenWidth/2 - currentMousePos.x),2) + pow((screenHeight/2) - currentMousePos.y,2)),
        BLACK
      );

      DrawRectangle(circleX-30.0f,circleY-60.0f - (10 * (7 - (distanceFromEye/100.0f))),60.0f,10.0f,BLACK);
      DrawLine(circleX-5.0f,circleY-60.0f - (10 * (7 - (distanceFromEye/100.0f))),circleX+5.0f,circleY-60.0f - (10 * (7 - (distanceFromEye/100.0f))),BLACK);
    //rotateX3d(0.06f * smallShapeRate * cos((smallShapeRate/0.2f) * PI / 2), smallShape);
      if(IsKeyDown(KEY_SPACE))
      {
        // pusing back a lazer for both eyes
        lazerHolder.push_back
        (
          lazer
          (
            Vector2
            {
              pupilX + (10 * ((currentMousePos.x / pupilX) - 1.0f)) + (3 * cos((smallShapeRate / 0.2f) * PI / 2)),
              pupilY + (10 * ((currentMousePos.y / pupilY) - 1.0f)) + (3 * cos((smallShapeRate / 0.2f) * PI / 2))
            },
            currentMousePos
          )
        );
      }
    }


    for(int i=0;i<points.size();++i)
    {
      DrawLine(points[i].x + screenWidth/2,points[i].y + screenHeight/2,smallShape[i].x + currentMousePos.x,smallShape[i].y + currentMousePos.y,RED);
    }

    for(int i=0;i<smallShape.size();++i)
    {
      DrawCircle(smallShape[i].x + currentMousePos.x,smallShape[i].y + currentMousePos.y,3.0f,RED);
      for(int j=0;j<smallShape.size();++j)
      {
        DrawLine(smallShape[j].x + currentMousePos.x,smallShape[j].y + currentMousePos.y,smallShape[(i + 1) % smallShape.size()].x + currentMousePos.x,smallShape[(i + 1) % smallShape.size()].y + currentMousePos.y,BLACK);

      }
    }

    for(int i=0;i<lazerHolder.size();++i)
    {
      lazerHolder[i].drawLazer();
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
