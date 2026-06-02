#include <stdio.h>

// 計算関数宣言
int Add(int a, int b);
int Sub(int a, int b);
int Mul(int a, int b);
int Div(int a, int b);

int main(void)
{
	// 関数ポインタ変数culcは計算関数を参照できる
	int (*culc)(int, int) = Add;

	// culc変数が参照している関数を呼ぶことができる
	int result = culc(10, 2);

	printf_s("計算結果：%d", result);
	return 0;
}

int Add(int a, int b) { return a + b; }
int Sub(int a, int b) { return a - b; }
int Mul(int a, int b) { return a * b; }
int Div(int a, int b) { return a / b; }



#if 0


// ゲームの状態
enum GameState
{
	INIT,
	STEP,
	DRAW,
	FIN
};
GameState g_State = INIT;

// ゲーム関数宣言
void Init();
void Step();
void Draw();
void Fin();

int main(void)
{
	// switch文はどうしても長くなりがち。。。
	//GameState state = INIT;
	//switch (state)
	//{
	//case INIT:
	//	Init();
	//	break;

	//case STEP:
	//	Step();
	//	break;

	//case DRAW:
	//	Draw();
	//	break;

	//case FIN:
	//	Fin();
	//	break;
	//}

	// 関数ポインタ配列なら短くてすっきり
	void (*func[])() = { Init, Step, Draw, Fin };

	// g_Stateに該当する関数が呼ばれる
	func[g_State]();

	return 0;
}

void Init() { printf_s("初期化処理です"); }
void Step() { printf_s("ステップ処理です"); }
void Draw() { printf_s("描画処理です"); }
void Fin() { printf_s("終了処理です"); }

// 練習用の構造体
struct GameObject
{
	float x;
	float y;
	float w;
	float h;
	void(*onCollision)(GameObject);	// 当たった時に呼ばれる関数
};

// 練習用当たり判定関数
void OnCollision(GameObject other);

int main(void)
{
	GameObject player = {};
	player.x = 50.0f;
	player.y = 120.0f;
	player.w = 20.0f;
	player.h = 20.0f;
	player.onCollision = OnCollision;

	GameObject enemy = {};
	enemy.x = 60.0f;
	enemy.y = 130.0f;
	enemy.w = 30.0f;
	enemy.h = 40.0f;

	// 当たり判定
	if (player.x  < (enemy.x + enemy.w) && (player.x + player.w) > enemy.x &&
		player.y  < (enemy.y + enemy.h) && (player.y + player.h) > enemy.y)
	{
		// 当たった時のイベント処理
		player.onCollision(enemy);
	}
}

void OnCollision(GameObject other)
{
	printf_s("当たったやつの座標（%.2f, %.2f）", other.x, other.y);
}


#endif

