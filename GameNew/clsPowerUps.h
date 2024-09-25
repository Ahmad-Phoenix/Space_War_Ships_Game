#pragma once
#include "clsRandom.h"
#include "GameConfig.h"
#include <string>
#include <vector>

class clsPowerUps
{
private:
	const char _SuperShotShape = 'B';
	const char _SuperSpeedShape = 'S';
	const char _HealthShape = 'H';
	const char _CoinsShape = '$';

	short _SPEED;
	float _PUX;
	float _PUY;
	float _Duration;
	int _TotalPowerUpsPickups;
	float _PowUpsDur = 600.00f;
	short _Width;
	vector <char> _vPowerUps;
	wstring* _Map;
	char _CurrentPowerUps;
	bool _SuperShoot = false;
	bool _SuperSpeed = false;

	class clsHandlePowerUps
	{
		private:
			enum enPowerUps;

		const float _SuperSpeed = 2.5f;

		float _PUX;
		float _PUY;
		char _CurrentPowerUps;

		float _Duration = 600;
		bool _IsPickup = false;
		bool _IsReachTarget = false;


		float _SuperSpeedPowerUps() const
		{
			return _SuperSpeed;
		}

		float _SuperShotPowerUps()
		{
			// <=> -1
			// \/-  0
			// <||=====> 1
			// \/-  2
			// <=>  3

			const float Start = -1;
			const float To = 3;

			float SuperShot = clsRandom<short>::RandomNumber(Start, To);

			return SuperShot;
		}

		bool _IsPickupPowerUps() const
		{
			if (_IsReachTarget)
			{
				return true;
			}
			return false;
		}

	public:
		enum enPowerUps { SuperSpeed = 'S', SuperShot = 'B' };

		clsHandlePowerUps(bool IsReachTarget, float PUX, float PUY, char CurrentPowerUps)
		{
			_IsReachTarget = IsReachTarget;
			_PUX = PUX;
			_PUY = PUY;
			_CurrentPowerUps = CurrentPowerUps;
		}

		bool IsPickup() const
		{
			return _IsPickup;
		}

		void SetPickup(const bool& IsPickup)
		{
			_IsPickup = IsPickup;
		}

		void SetDuration(const float& Duration)
		{
			_Duration -= Duration;
		}

		float Duration() const
		{
			return _Duration;
		}

		float DurationTimer() const
		{
			return _Duration / 60;
		}

		void ActivePowerUps()
		{
			if (_IsPickupPowerUps())
			{
				_IsPickup = true;
			}
		}

		float GetCurrentPowerUps()
		{
			char CurrentPowerUpType = CurrentPowerUpsType();

			if (CurrentPowerUpType == enPowerUps::SuperSpeed)
			{
				return _SuperSpeedPowerUps();
			}
			else if (CurrentPowerUpType == enPowerUps::SuperShot)
			{
				return _SuperShotPowerUps();
			}
			else
			{
				// Here else is too important besuse will return a value of 495 
				return _SuperShotPowerUps();

			}
		}

		char CurrentPowerUpsType() const
		{
			switch (static_cast<enPowerUps>(_CurrentPowerUps))
			{
				case enPowerUps::SuperSpeed:
				{
					return static_cast<char>(enPowerUps::SuperSpeed);
					break;
				}
				case enPowerUps::SuperShot:
				{
					return static_cast<char>(enPowerUps::SuperShot);
					break;
				}
				default:
				{
					return static_cast<char>(enPowerUps::SuperShot);
					break;
				}
			}
		}


	};

	float _ActiveSuperPower(bool& SuperPowerType, clsHandlePowerUps& HandlePowerUps)
	{
		HandlePowerUps.ActivePowerUps();

		if (HandlePowerUps.IsPickup() && !SuperPowerType)
		{
			SuperPowerType = true;
			return HandlePowerUps.GetCurrentPowerUps();
		}
		else if (SuperPowerType)
		{
			_Duration++;
			HandlePowerUps.SetDuration(_Duration);

			_PowUpsDur = HandlePowerUps.Duration();

			if (_PowUpsDur > 0.0f)
			{
				return HandlePowerUps.GetCurrentPowerUps();
			}
			else
			{
				_Duration = 0;
				_PowUpsDur = 600;
				SuperPowerType = false;
				HandlePowerUps.SetPickup(false);
				return HandlePowerUps.GetCurrentPowerUps();
			}
		}

		return HandlePowerUps.GetCurrentPowerUps();


	}

	bool _AreSuperShootActiveted() const
	{
		return _SuperShoot;
	}

	bool _AreSuperSpeedActiveted() const
	{

		return _SuperSpeed;
	}

	void _ClearPositIon()
	{
		(*_Map)[_PUX * _Width + _PUY] = ' ';
	}

	void _RestValue()
	{
		_ClearPositIon();
		_PUX = 0.00f;
		_PUY = 0.00f;
	}

	bool _IsPickupSuperShotShape() const
	{
		return (_SuperShotShape == _CurrentPowerUps);
	}

	bool _IsPickupSuperSpeedShape() const
	{
		return (_SuperSpeedShape == _CurrentPowerUps);
	}

	bool _IsPickupHealthShape() const
	{
		return (_HealthShape == _CurrentPowerUps);
	}

	bool _IsPickupCoinsShape() const
	{
		return (_CoinsShape == _CurrentPowerUps);
	}


public:

	clsPowerUps(float SPEED, const vector <char>& vPowerUps, wstring* Map, const short& Width)
	{
		_SPEED = SPEED;
		_vPowerUps = vPowerUps;
		_Map = Map;
		_Width = Width;
	}

	clsPowerUps(float SPEED, const char& PowerUpsShape, wstring* Map, const short& Width)
	{
		_SPEED = SPEED;
		_CurrentPowerUps = PowerUpsShape;
		_Map = Map;
		_Width = Width;
	}

	float ActiveSuperShootPower()
	{
		bool AreReachTarget = IsReachTarget(*GameConfig::PlayerShip::fPlayerX, *GameConfig::PlayerShip::fPlayerY);

		if (AreReachTarget)
		{
			_TotalPowerUpsPickups++;
			_RestValue();
		}

		clsHandlePowerUps HandlePowerUps(AreReachTarget, _PUX, _PUY, _CurrentPowerUps);

		if (HandlePowerUps.CurrentPowerUpsType() == HandlePowerUps.SuperShot)
		{
			return _ActiveSuperPower(_SuperShoot, HandlePowerUps);
		}

	}
	
	bool ArePickUpSuperShoot() const
	{
		if ((_AreSuperShootActiveted() || IsReachTarget(*GameConfig::PlayerShip::fPlayerX, *GameConfig::PlayerShip::fPlayerY)) && _IsPickupSuperShotShape())
			return true;
		else
			return false;
	}
	
	float ActiveSuperSpeedPower()
	{
		bool AreReachTarget = IsReachTarget(*GameConfig::PlayerShip::fPlayerX, *GameConfig::PlayerShip::fPlayerY);

		if (AreReachTarget)
		{
			_TotalPowerUpsPickups++;
			_RestValue();
		}

		clsHandlePowerUps HandlePowerUps(AreReachTarget, _PUX, _PUY, _CurrentPowerUps);

		if (HandlePowerUps.CurrentPowerUpsType() == HandlePowerUps.SuperSpeed)
		{
			return _ActiveSuperPower(_SuperSpeed, HandlePowerUps);
		}

	}

	bool ArePickUpSuperSpeed() const
	{
		if ((_AreSuperSpeedActiveted() || IsReachTarget(*GameConfig::PlayerShip::fPlayerX, *GameConfig::PlayerShip::fPlayerY)) && _IsPickupSuperSpeedShape())
			return true;
		else
			return false;
	}

	bool IsActive() const
	{
		return (_PUY - 1 > 0);

	}
	
	bool IsReachTarget(const float& TargetX, const float& TargetY) const
	{
		bool IsTargetPickupPowerUps = (TargetX - 1 == _PUX || TargetX == _PUX || TargetX + 1 == _PUX || TargetX + 2 == _PUX || TargetX + 3 == _PUX);

		if (IsTargetPickupPowerUps)
			return (_PUY == TargetY);
		else
			return false;

	}
	
	void Speed(const float& speed)
	{
		_SPEED = speed;
	}

	float Duration() const
	{
		return (_PowUpsDur / 60);
	}

	char GenerateRandomPowersUps()
	{
		_ClearPositIon();

		char RandomPowersUps = _vPowerUps[clsRandom<short>::RandomNumber(0, _vPowerUps.size() - 1)];
		const short _Spawn = -20;
		clsRandom<short>::_GenerateRandomObject(_PUX, _PUY, *_Map, RandomPowersUps, _Spawn);
		_CurrentPowerUps = (*_Map)[_PUX * _Width + _PUY];
		return _CurrentPowerUps;
	}

	bool Update(char PowerUpsShape)
	{
		_ClearPositIon();

		if (IsActive())
		{
			_PUY -= _SPEED;
			(*_Map)[_PUX * _Width + _PUY] = PowerUpsShape;
			return true;
		}
		return false;

	}

	bool Update()
	{
		return Update(_CurrentPowerUps);
	}

	int TotalPowerUpsPickups() const
	{
		return _TotalPowerUpsPickups;
	}

	void Clear()
	{
		_RestValue();
		_TotalPowerUpsPickups = 0;
	}
};

