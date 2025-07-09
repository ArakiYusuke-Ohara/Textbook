#pragma once

class Easing 
{
public:
	Easing();
	~Easing();

public:
	void Play(int type, int time, bool reverse = false);
	void Update();

	void SetActive(bool active) { m_Active = active; }
	void SetAutoDelete(bool flag) { m_AutoDelete = flag; }

	bool IsActive() const { return m_Active; }
	bool IsEnd()	const { return m_TimeCounter >= m_Time; }
	float GetValue() const { return m_Value; }

private:
	static float EaseInSlide(float progress);
	static float EaseOutSlide(float progress);
	static float EaseOutElastic(float progress);
	static float EaseInOutElastic(float progress);

private:
	bool m_Active;
	bool m_AutoDelete;
	bool m_Reverse;
	int m_Type;
	int m_Time;
	int m_TimeCounter;
	float m_Progress;
	float m_Value;
	static float(* m_EasingFunc[4])(float);

};