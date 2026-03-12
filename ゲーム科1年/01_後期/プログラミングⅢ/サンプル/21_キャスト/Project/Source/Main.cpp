#include <list>
#include <iostream>

using namespace std;

class Food
{
public:
	Food() { m_Price = 0; }
	virtual ~Food() {}
protected:
	int m_Price;
};

class Fruit : public Food
{
public:
	void SetFarmName(const char* name) { strcpy_s(m_FarmName, name); }
	char* GetFarmName() { return m_FarmName; }
private:
	char m_FarmName[256];
};

class Meat : public Food
{
public:
	void SetStoreName(const char* name) { strcpy_s(m_StoreName, name); }
	char* GetStoreName() { return m_StoreName; }
private:
	char m_StoreName[256];
};

// static_cast
//int main()
//{
//	// Fruitを生成してFoodポインタで参照
//	Food* food = new Fruit;
//
//	// static_castは明示的なキャスト
//	// これまでのものと同じ
//	// FoodポインタをFruitポインタにキャストする
//	Fruit* fruit = static_cast<Fruit*>(food);
//
//	// FruitにキャストしたのでFruitの関数が呼べる
//	fruit->SetFarmName("荒木農園");
//
//	cout << fruit->GetFarmName() << endl;
//
//	return 0;
//}

// dynamic_cast
//int main()
//{
//	// Fruitを生成してFoodポインタで参照
//	Food* food = new Fruit;
//	
//	// dynamic_castはダウンキャストについてチェックする機能がある
//	// 生成されたクラスとは違うクラスにキャストしようとすると
//	// nullptrが返却される
//	// Fruitで生成したのにMeatにキャストしようとしている
//	Meat* meat = dynamic_cast<Meat*>(food);
//	
//	// FruitをMeatに不正にキャストしてしまったのでmeatにはnullptrが入っている
//	if (meat)
//	{
//		// ここは処理できない
//		meat->SetStoreName("本田精肉店");
//		cout << meat->GetStoreName() << endl;
//	}
//		
//	return 0;
//}

// const_cast
//int main()
//{
//	// constなので数値は100から変更できないはずが
//	const int ENEMY_POWER = 100;
//
//	// const_castでポインタにキャストすると
//	int* power = const_cast<int*>(&ENEMY_POWER);
//
//	// const定数を書き換えることができてしまう
//	*power = 500;
//
//	// ブレークポイントで止めてENEMY_POWERを見てみましょう
//	return 0;
//}

// reinterpret_cast
int main()
{
	// reinterpret_castはどんな
	// ポインタに対してアドレスを直接数値を設定することができる
	// fruitはメモリの500番地を指すことになる
	Fruit* fruit = reinterpret_cast<Fruit*>(500);

	cout << "fruit = " << fruit << endl;

	return 0;
}
