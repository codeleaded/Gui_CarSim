#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/GSprite.h"
#include "/home/codeleaded/System/Static/Library/NeuralNetwork.h"
#include "/home/codeleaded/System/Static/Library/AffineTransform.h"


Vec2 pos;
float s;
float a;

AffineTransform transform;
Sprite sp;

void Setup(AlxWindow* w){
    ResizeAlxFont(8,8);

    transform = AffineTransform_New();
    sp = Sprite_Load("./data/Car_Green_Fast.png");

    pos.x = 0.0f;
    pos.y = 0.0f;
    s = 1.0f;
    a = 0.0f;
}
void Update(AlxWindow* w){
    Vec2 front = Vec2_Mulf(Vec2_OfAngle(-a),400.0f * w->ElapsedTime);

    if(Stroke(ALX_KEY_W).DOWN)      pos = Vec2_Add(pos,front);
    if(Stroke(ALX_KEY_S).DOWN)      pos = Vec2_Sub(pos,front);
    if(Stroke(ALX_KEY_A).DOWN)      pos = Vec2_Add(pos,Vec2_Perp(front));
    if(Stroke(ALX_KEY_D).DOWN)      pos = Vec2_Sub(pos,Vec2_Perp(front));
    
    if(Stroke(ALX_KEY_UP).DOWN)     s -= 1.0f * w->ElapsedTime;
    if(Stroke(ALX_KEY_DOWN).DOWN)   s += 1.0f * w->ElapsedTime;
    
    if(Stroke(ALX_KEY_LEFT).DOWN)   a -= 1.0f * w->ElapsedTime;
    if(Stroke(ALX_KEY_RIGHT).DOWN)  a += 1.0f * w->ElapsedTime;

    Clear(DARK_BLUE);

    AffineTransform_Identity(&transform);
    //AffineTransform_Trans(&transform,(Vec2){ x,y });
    AffineTransform_Trans(&transform,(Vec2){ -(float)sp.w * 0.5f,-(float)sp.h * 0.5f });
    //AffineTransform_Trans(&transform,(Vec2){ -x,-y });
    AffineTransform_RotateZ(&transform,a);
    AffineTransform_Trans(&transform,(Vec2){ (float)sp.w * 0.5f,(float)sp.h * 0.5f });
    AffineTransform_Scale(&transform,(Vec2){ s,s });
    
    Rect area = AffineTransform_Rect(&transform,(Rect){ 0.0f,0.0f,sp.w,sp.h });
    AffineTransform_Inverse(&transform);

    for(int i = 0;i<area.d.y;i++){
        for(int j = 0;j<area.d.x;j++){
            const Vec2 rp = { area.p.x + j,area.p.y + i };
            const Vec2 p = AffineTransform_Calc(&transform,rp);
            const Pixel col = Sprite_Get(&sp,p.x,p.y);
            RenderPixel(pos.x + rp.x,pos.y + rp.y,col);
        }
    }
}
void Delete(AlxWindow* w){
    Sprite_Free(&sp);
}

int main(){
    if(Create("Car Simulation",1900,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}
