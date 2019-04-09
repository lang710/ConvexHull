#include <iostream>
#include <cmath>
#include <vector>
#define PI 3.1415926
using namespace std;

struct point{
    float x,y;
};


int main(){

    int p_size;
    cin>>p_size;
    point points[p_size];
    int i,j;
    for(i=0;i<p_size;i++)
        cin>>points[i].x>>points[i].y;

    point basepoint=points[0];
    for(i=0;i<p_size;i++)
        if(basepoint.y>points[i].y||(basepoint.y==points[i].y&&basepoint.x<points[i].x))
            basepoint=points[i];

    float angle1,angle2,distance1,distance2;
    //对点集以basepoint为原点进行极角排序
    for(i=0;i<p_size-1;i++)
        for(j=i;j<p_size+1;j++) {
            if(points[i].x==basepoint.x)
                if(points[i].y==basepoint.y)
                    angle1=0;
                else
                    angle1=PI/2;
            else if(points[i].x<basepoint.x)
                angle1=PI+atan((points[i].y - basepoint.y) / (points[i].x - basepoint.x));
            else
                angle1=atan((points[i].y - basepoint.y) / (points[i].x - basepoint.x));

            if(points[j].x==basepoint.x)
                angle2=PI/2;
            else if(points[j].x<basepoint.x)
                angle2=PI+atan((points[j].y - basepoint.y) / (points[j].x - basepoint.x));
            else
                angle2=atan((points[j].y - basepoint.y) / (points[j].x - basepoint.x));

            if (angle1>angle2){
                swap(points[i],points[j]);
            }else if(angle1==angle2){
                distance1=pow(points[i].x-basepoint.x,2)+pow(points[i].y-basepoint.y,2);
                distance2=pow(points[j].x-basepoint.x,2)+pow(points[j].y-basepoint.y,2);
                if(distance1>distance2)
                    swap(points[i],points[j]);
            }

        }

    vector<point> p_stack;
    p_stack.push_back(points[p_size-1]);
    p_stack.push_back(points[0]);
    point p1,p2,p3;
    float D;

    for(i=1;i<p_size-1;i++){
        p1=p_stack[p_stack.size()-2];
        p2=p_stack[p_stack.size()-1];
        p3=points[i];

        D=(p1.x-p3.x)*p2.y+(p3.x-p2.x)*p1.y+(p2.x-p1.x)*p3.y;       //计算符号面积，判断左旋右旋或者三点共线
        if(D>0)
            p_stack.push_back(p3);                      //左旋入栈
        else{
            p_stack.pop_back();                         //右旋或者三点共线出栈
            i--;
        }
    }

    for(i=0;i<p_stack.size();i++)
        cout<<p_stack[i].x<<' '<<p_stack[i].y<<endl;

    return 0;
}

/*
 *
input:
10
133.0 1.0
544.0 71.0
558.0 206.0
536.0 338.0
463.0 436.0
330.0 503.0
188.0 499.0
305.0 2.0
55.0 410.0
2.0 140.0

output:
2 140
133 1
305 2
544 71
558 206
536 338
463 436
330 503
188 499
55 410
 *
 */
