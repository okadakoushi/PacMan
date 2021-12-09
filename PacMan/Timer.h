#pragma once

/// <summary>
/// タイム。
/// </summary>
class Timer
{
private:
	static Timer* m_instance;
	LONG m_begin;
	LONG m_freq;
	LONG m_end;
	double m_elapsed = 0.0f;

private:
	Timer() {};

public:
	/// <summary>
	/// タイムクラスの取得。
	/// </summary>
	/// <returns></returns>
	static Timer* GetInstance()
	{
		if (!m_instance) {
			m_instance = new Timer;
		}
		return m_instance;
	}
	/// <summary>
	/// 計測開始。
	/// </summary>
	void StartTimer();

	/// <summary>
	/// 計測終了。
	/// </summary>
	void StopTimer();

	/// <summary>
	/// 経過時間を取得。
	/// </summary>
	/// <returns></returns>
	double GetDeltaTime()
	{
		return m_elapsed;
	}
};


static inline Timer* GameTime()
{
	return Timer::GetInstance();
}

