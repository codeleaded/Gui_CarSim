#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/ASprite.h"


Vec2 pos;
float vel;
ASprite car;

void Setup(AlxWindow* w){
    ResizeAlxFont(8,8);

    car = ASprite_New("./data/Car_Green_Fast.png");
    pos = (Vec2){ 0.0f,0.0f };
    vel = 0.0f;
}
void Update(AlxWindow* w){
    Vec2 front = Vec2_Mulf(Vec2_OfAngle(-car.a),1000.0f * w->ElapsedTime);

    if(Stroke(ALX_KEY_W).DOWN)      vel += 1000.0f * w->ElapsedTime;
    if(Stroke(ALX_KEY_S).DOWN)      vel -= 1000.0f * w->ElapsedTime;
    if(Stroke(ALX_KEY_SPACE).DOWN)  vel *= 0.975f;
    
    if(Stroke(ALX_KEY_UP).DOWN)     ASprite_Update(&car,car.s + 1.0f * w->ElapsedTime,car.a);
    if(Stroke(ALX_KEY_DOWN).DOWN)   ASprite_Update(&car,car.s - 1.0f * w->ElapsedTime,car.a);
    
    if(Stroke(ALX_KEY_LEFT).DOWN)   ASprite_Update(&car,car.s,car.a + F32_PI * w->ElapsedTime);
    if(Stroke(ALX_KEY_RIGHT).DOWN)  ASprite_Update(&car,car.s,car.a - F32_PI * w->ElapsedTime);
    
    vel *= 0.999f;
    pos = Vec2_Add(pos,Vec2_Mulf(Vec2_OfAngle(-car.a),vel * w->ElapsedTime));
    
    Clear(DARK_BLUE);

    ASprite_Render(WINDOW_STD_ARGS,&car,pos.x,pos.y);
}
void Delete(AlxWindow* w){
    ASprite_Free(&car);
}

int main(){
    if(Create("Car Simulation",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}
