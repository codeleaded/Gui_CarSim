#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/TDWorld.h"


TDWorld world;

void Setup(AlxWindow* w){
    ResizeAlxFont(10,10);

    if(Files_isFile("./data/World0.dtworld")){
        world = TDWorld_Load("./data/World0.dtworld",(Sprite[]){
            Sprite_Load("./assets/Track_Right.png"),
            Sprite_Load("./assets/Track_Top.png"),
            Sprite_Load("./assets/Track_Right_Pedest.png"),
            Sprite_Load("./assets/Track_Top_Pedest.png"),
            Sprite_Load("./assets/Track_Right_Curve.png"),
            Sprite_Load("./assets/Track_Top_Curve.png"),
            Sprite_Load("./assets/Track_Left_Curve.png"),
            Sprite_Load("./assets/Track_Down_Curve.png"),
            Sprite_Load("./assets/Track_Right_Cross.png"),
            Sprite_Load("./assets/Track_Top_Cross.png"),
            Sprite_Load("./assets/Track_Left_Cross.png"),
            Sprite_Load("./assets/Track_Down_Cross.png"),
            Sprite_Load("./assets/Track_Middle.png"),
            Sprite_None()
        });
    }else{
        world = TDWorld_New(100,100,(Sprite[]){
            Sprite_Load("./assets/Track_Right.png"),
            Sprite_Load("./assets/Track_Top.png"),
            Sprite_None()
        });
    }
    TDWorld_LoadCar(&world,50.0f,50.0f,"./assets/Car_Green_Fast.png");

    world.tv.Scale = (Vec2){ 0.1f,0.1f };
}
void Update(AlxWindow* w){
    TransformedView_HandlePanZoom(&world.tv,w->Strokes,(Vec2){ (float)w->MouseX,(float)w->MouseY });
    TransformedView_Focus(&world.tv,&world.car.pos,(Vec2){ world.car.car.sprite.w,world.car.car.sprite.h });
    
    if(Stroke(ALX_MOUSE_L).PRESSED){
        const Vec2 m_world = TransformedView_ScreenWorldPos(&world.tv,(Vec2){ (float)w->MouseX,(float)w->MouseY });
        if(m_world.x >= 0 && m_world.x < (int)world.width && m_world.y >= 0 && m_world.y < (int)world.height){
            const unsigned int tx = (unsigned int)m_world.x;
            const unsigned int ty = (unsigned int)m_world.y;
            const unsigned int index = ty * world.width + tx;
            world.world[index] = (world.world[index] + 1) % (world.sprites.size + 1);
        }
    }


    if(Stroke(ALX_KEY_W).DOWN)          TDCar_Acc(&world.car, 1.0f,w->ElapsedTime);
    if(Stroke(ALX_KEY_S).DOWN)          TDCar_Acc(&world.car,-1.0f,w->ElapsedTime);
    if(Stroke(ALX_KEY_A).DOWN)          TDCar_Turn(&world.car, F32_PI * w->ElapsedTime);
    if(Stroke(ALX_KEY_D).DOWN)          TDCar_Turn(&world.car,-F32_PI * w->ElapsedTime);
    
    if(Stroke(ALX_KEY_SPACE).DOWN)      TDCar_Break(&world.car,0.98f);
    if(Stroke(ALX_KEY_ENTER).DOWN)      TDCar_Start(&world.car);

    if(Stroke(ALX_KEY_R).PRESSED)       TDCar_Gear(&world.car,world.car.gear + 1);
    if(Stroke(ALX_KEY_F).PRESSED)       TDCar_Gear(&world.car,world.car.gear - 1);
    
    
    TDCar_Update(&world.car,w->ElapsedTime);
    
    Clear(LIGHT_BLUE);

    //TDCar_Render(WINDOW_STD_ARGS,&car);

    TDWorld_Render(WINDOW_STD_ARGS,&world);

    TDCar_RenderSpeed(WINDOW_STD_ARGS,&window.AlxFont,&world.car,200.0f,GetHeight() - 200.0f,200.0f);
    TDCar_RenderWTN(WINDOW_STD_ARGS,&window.AlxFont,&world.car,600.0f,GetHeight() - 200.0f,200.0f);
}
void Delete(AlxWindow* w){
    TDWorld_Save(&world,"./data/World0.dtworld");
    TDWorld_Free(&world);
}

int main(){
    if(Create("Car Simulation",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}
