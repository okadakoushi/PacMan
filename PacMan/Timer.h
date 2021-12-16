#pragma once

/// <summary>
/// �^�C���B
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
	/// �^�C���N���X�̎擾�B
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
	/// �v���J�n�B
	/// </summary>
	void StartTimer();

	/// <summary>
	/// �v���I���B
	/// </summary>
	void StopTimer();

	/// <summary>
	/// �o�ߎ��Ԃ��擾�B
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

