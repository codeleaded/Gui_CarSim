#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TDCar.h"


TDCar car;

void Setup(AlxWindow* w){
    ResizeAlxFont(8,8);

    car = TDCar_New((Vec2){ 0.0f,0.0f },"./data/Car_Green_Fast.png");
}
void Update(AlxWindow* w){
    if(Stroke(ALX_KEY_W).DOWN)          TDCar_Acc(&car, 1.0f,w->ElapsedTime);
    if(Stroke(ALX_KEY_S).DOWN)          TDCar_Acc(&car,-1.0f,w->ElapsedTime);
    if(Stroke(ALX_KEY_SPACE).DOWN)      TDCar_Break(&car,0.98f);
    if(Stroke(ALX_KEY_ENTER).DOWN)      TDCar_Start(&car);
    
    //if(Stroke(ALX_KEY_UP).DOWN)       TDCar_Scale(&car, 1.0f * w->ElapsedTime);
    //if(Stroke(ALX_KEY_DOWN).DOWN)     TDCar_Scale(&car,-1.0f * w->ElapsedTime);

    if(Stroke(ALX_KEY_UP).PRESSED)      TDCar_Gear(&car,car.gear + 1);
    if(Stroke(ALX_KEY_DOWN).PRESSED)    TDCar_Gear(&car,car.gear - 1);
    
    if(Stroke(ALX_KEY_LEFT).DOWN)       TDCar_Turn(&car, F32_PI * w->ElapsedTime);
    if(Stroke(ALX_KEY_RIGHT).DOWN)      TDCar_Turn(&car,-F32_PI * w->ElapsedTime);
    
    TDCar_Update(&car,w->ElapsedTime);
    
    Clear(DARK_BLUE);

    TDCar_Render(WINDOW_STD_ARGS,&car);
    TDCar_RenderSpeed(WINDOW_STD_ARGS,&car,200.0f,GetHeight() - 200.0f,200.0f);
    TDCar_RenderWTN(WINDOW_STD_ARGS,&car,600.0f,GetHeight() - 200.0f,200.0f);
}
void Delete(AlxWindow* w){
    TDCar_Free(&car);
}

int main(){
    if(Create("Car Simulation",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}
