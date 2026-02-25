#include <stdio.h>

// ゲームの状態
enum GameState
{
	INIT,
	STEP,
	DRAW,
	FIN
};

// 練習用の構造体
struct GameObject
{
	float x;
	float y;
	float w;
	float h;
	void(*oce)(GameObject);	// 当たった時に呼ばれる関数
};

// 計算関数宣言
int Add(int a, int b);
int Sub(int a, int b);
int Mul(int a, int b);
int Div(int a, int b);

// ゲーム関数宣言
void Init();
void Step();
void Draw();
void Fin();

// 練習用当たり判定関数
void OnCollisionEnter(GameObject other);

#if 0
int main(void)
{
	// 関数ポインタ変数culcには計算関数を参照できる
	int (*culc)(int, int) = Add;
	// culc変数が参照している関数を呼ぶことができる
	int result = culc(10, 2);
	printf_s("計算結果：%d", result);

	return 0;
}

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
	void (*func[])() = {Init, Step, Draw, Fin};

	GameState state = INIT;
	func[state]();

	return 0;
}
#endif
int main(void)
{
	GameObject player = {};
	player.x = 50.0f;
	player.y = 120.0f;
	player.w = 20.0f;
	player.h = 20.0f;
	player.oce = OnCollisionEnter;

	GameObject enemy = {};
	enemy.x = 60.0f;
	enemy.y = 130.0f;
	enemy.w = 30.0f;
	enemy.h = 40.0f;

	// 当たり判定
	if (player.x  < (enemy.x + enemy.w) && (player.x + player.w) > enemy.x &&
		player.y  < (enemy.y + enemy.h) && (player.y + player.h) > enemy.y)
	{
		// 当たった時に呼ばれる関数を呼ぶ
		player.oce(enemy);
	}
}

int Add(int a, int b)
{
	return a + b;
}

int Sub(int a, int b)
{
	return a - b;
}

int Mul(int a, int b)
{
	return a * b;
}

int Div(int a, int b)
{
	return a / b;
}

void Init()
{
	printf_s("初期化処理です");
}

void Step()
{
	printf_s("ステップ処理です");
}

void Draw()
{
	printf_s("描画処理です");
}

void Fin()
{
	printf_s("終了処理です");
}

void OnCollisionEnter(GameObject other)
{
	printf_s("当たったやつの座標（%.2f, %.2f）", other.x, other.y);
}

