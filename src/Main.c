#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TDWorld.h"


TDWorld world;

void Setup(AlxWindow* w){
    ResizeAlxFont(10,10);

    world = TDWorld_New(100,100,(Sprite[]){
        Sprite_Load("./data/Track_Right.png"),
        Sprite_Load("./data/Track_Top.png"),
        Sprite_None()
    });
    TDWorld_LoadCar(&world,50.0f,50.0f,"./data/Car_Green_Fast.png");
}
void Update(AlxWindow* w){
    TransformedView_HandlePanZoom(&world.tv,w->Strokes,(Vec2){ (float)w->MouseX,(float)w->MouseY });
    TransformedView_Focus(&world.tv,&world.car.pos);
    
    if(Stroke(ALX_MOUSE_L).PRESSED){
        const Vec2 m_world = TransformedView_ScreenWorldPos(&world.tv,(Vec2){ (float)w->MouseX,(float)w->MouseY });
        if(m_world.x >= 0 && m_world.x < (int)world.width && m_world.y >= 0 && m_world.y < (int)world.height){
            const unsigned int tx = (unsigned int)m_world.x;
            const unsigned int ty = (unsigned int)m_world.y;
            const unsigned int index = ty * world.width + tx;
            world.world[index] = (world.world[index] + 1) % 3;
        }
    }


    if(Stroke(ALX_KEY_W).DOWN)          TDCar_Acc(&world.car, 1.0f,w->ElapsedTime);
    if(Stroke(ALX_KEY_S).DOWN)          TDCar_Acc(&world.car,-1.0f,w->ElapsedTime);
    if(Stroke(ALX_KEY_SPACE).DOWN)      TDCar_Break(&world.car,0.98f);
    if(Stroke(ALX_KEY_ENTER).DOWN)      TDCar_Start(&world.car);

    if(Stroke(ALX_KEY_UP).PRESSED)      TDCar_Gear(&world.car,world.car.gear + 1);
    if(Stroke(ALX_KEY_DOWN).PRESSED)    TDCar_Gear(&world.car,world.car.gear - 1);
    
    if(Stroke(ALX_KEY_LEFT).DOWN)       TDCar_Turn(&world.car, F32_PI * w->ElapsedTime);
    if(Stroke(ALX_KEY_RIGHT).DOWN)      TDCar_Turn(&world.car,-F32_PI * w->ElapsedTime);
    
    TDCar_Update(&world.car,w->ElapsedTime);
    
    Clear(DARK_BLUE);

    //TDCar_Render(WINDOW_STD_ARGS,&car);

    TDWorld_Render(WINDOW_STD_ARGS,&world);

    TDCar_RenderSpeed(WINDOW_STD_ARGS,&window.AlxFont,&world.car,200.0f,GetHeight() - 200.0f,200.0f);
    TDCar_RenderWTN(WINDOW_STD_ARGS,&window.AlxFont,&world.car,600.0f,GetHeight() - 200.0f,200.0f);
}
void Delete(AlxWindow* w){
    TDWorld_Free(&world);
}

int main(){
    if(Create("Car Simulation",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}
