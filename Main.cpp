#include "DxLib.h"
#include <vector>
#include <thread>
#include "Player.h"
#include "Bullet.h"

#include <chrono>

#include <atomic>
#include <mutex>

#include <stdio.h>

std::vector<Bullet*> bullets;

char key[256];      //キー取得用配列
int x = 300, y = 240;
double move;

int xcount = 0, ycount = 0;
int ix = 0, iy = 0, result = 0;

int bullet_num;
double theta;
double* bullet_angle;
//double bullet_angle[2];
bool bullet_draw = false;

//時間を計るようの変数
int count = 120;
auto start = std::chrono::system_clock::now();

//メモリバリア
std::atomic<bool> bullet_draw_atom(false);
std::mutex mtx;

void setup()
{
    printf("test");

    SetAlwaysRunFlag(TRUE);                 //ウィンドウがノンアクティブでも実行
    SetWindowSizeChangeEnableFlag(TRUE);    //ウィンドウサイズを自由に変更できる
    SetOutApplicationLogValidFlag(FALSE);   //ログ出力しない
    SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP); //フルスクリーン時に縦横比を維持する
    SetWindowText("シューティングゲーム");  //ウィンドウタイトルを付ける
    ChangeWindowMode(TRUE);                 //ウィンドウモードに変更
    SetGraphMode(960, 720, 32);             //画面サイズ指定

    bullet_num = 120;
    theta = 360.0 / bullet_num;
    bullet_angle = (double*)malloc(sizeof(double) * bullet_num);

    for (int i = 0; i < bullet_num; i++)
    {
        bullet_angle[i] = i * theta * 5.0;
        bullets.push_back(new Bullet(600, 500, bullet_angle[i], i)); //アクセス違反
    }
    move = 1.0f;
}

//キー入力の処理をするメソッド
void keyIn()
{
    if (key[KEY_INPUT_A] == 1 || key[KEY_INPUT_LEFT] == 1)
    {
        x -= (int)4 * move;
        if (xcount > 0) xcount = 0;
        --xcount;
    }
    if (key[KEY_INPUT_D] == 1 || key[KEY_INPUT_RIGHT] == 1)
    {
        x += (int)4 * move;
        if (xcount < 0) xcount = 0;
        ++xcount;
    }
    if (key[KEY_INPUT_W] == 1 || key[KEY_INPUT_UP] == 1)
    {
        y -= (int)4 * move;
        if (xcount > 0) ycount = 0;
        --ycount;
    }
    if (key[KEY_INPUT_S] == 1 || key[KEY_INPUT_DOWN] == 1)
    {
        y += (int)4 * move;
        if (ycount < 0) ycount = 0;
        ++ycount;
    }

    ix = abs(xcount) % 30 / 10;
    iy = abs(ycount) % 30 / 10;
    if (xcount > 0)
    {
        ix += 3;
        result = ix;
    }
    else if (xcount < 0)
    {
        ix += 9;
        result = ix;
    }
    if (ycount > 0)
    {
        iy += 3;
        result = iy;
    }
    else if (ycount < 0)
    {
        iy += 9;
        result = iy;
    }

    if (key[KEY_INPUT_LEFT] != 1 && key[KEY_INPUT_A] != 1
        && key[KEY_INPUT_RIGHT] != 1 && key[KEY_INPUT_D] != 1)
    {
        xcount = 0;
    }
    if (key[KEY_INPUT_W] != 1 || key[KEY_INPUT_UP] != 1
        && key[KEY_INPUT_S] != 1 || key[KEY_INPUT_DOWN] != 1)
    {
        ycount = 0;
    }
}

void thread_func(Player* player, int start, int end)
{
    //Bullet* bp;
    while (player -> isLife())
    {
        //if (bullet_draw)
        //{
        //    Bullet* bp = (Bullet *)bullets.at(0);
        //    /*for (int i = start; i < end; i++) {
        //        bullets[i]->moveBullet();
        //        if (player->isCollision(bullets[i]))
        //            player->playerDie();
        //    }*/
        //    try
        //    {
        //        bp->moveBullet(); //ここで書き込み中にアクセス違反が発生
        //    }
        //    catch (...)
        //    {
        //        
        //    }
        //    free(bp);
        //}
        if (bullet_draw_atom)
        {
            std::lock_guard<std::mutex> lock(mtx);
            {
                //Bullet* bp;
                for (int i = start; i < end; i++)
                {
                   /*bp = bullets.at(i);
                    bp->moveBullet();*/
                    bullets[i]->moveBullet();
                }
            }
        }
    }
}

void debug_drawString()
{
    Bullet** addr = &bullets[0];
    DrawString(100, 100, (char*)uint64_t(addr), GetColor(255, 255, 255));
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    setup();

    if (DxLib_Init() == -1) return -1;

    Player player(x, y);

    WaitKey();

    //std::thread th_a(thread_func, &player, 0, bullet_num);

    while (ScreenFlip() == 0 && ProcessMessage() == 0
        && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0)
    {
        debug_drawString();

        auto now = std::chrono::system_clock::now();
        std::chrono::duration<double, std::milli> elapsed = now - start;

        //if (elapsed.count() > 5)
        //{
        //    if(count < bullet_num)
        //        count++;
        //    start = std::chrono::system_clock::now();
        //}

        keyIn();
        if (key[KEY_INPUT_SPACE] == 1)
        {
            start = std::chrono::system_clock::now();

            //bullet_draw = true;
            bullet_draw_atom = true;
            
            //std::vector<Bullet*>::iterator it;
            //for (it = bullets.begin(); it != bullets.end(); ++it) *it;
            //for (Bullet* b : bullets) b->drawBullet();
        }

        //if (bullet_draw)
        //{
        //    for (Bullet* b : bullets)
        //    {
        //        b->moveBullet();
        //        if (player.isCollision(b))
        //            player.playerDie();
        //    }
        //}

        player.move(x, y);

        if (key[KEY_INPUT_ESCAPE] == 1) break;
    };

    //th_a.join();
    DxLib_End();

    std::vector<Bullet*>::iterator it;
    for (it = bullets.begin(); it != bullets.end(); ++it) delete *it;

    free(bullet_angle);

    return 0;
}
