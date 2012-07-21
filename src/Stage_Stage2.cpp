#include "DXUT.h"
#include "Stage_Stage2.h"
#include "Include_Entities.h"
#include "Include_Managers.h"
#include "Include_Adders.h"
#include "Helper.h"
#include "Stage2_Wrapper.h"

#define MAX_BULLETS 10

using namespace std;

Stage_Stage2::Stage_Stage2(void)
{

}

Stage_Stage2::~Stage_Stage2(void)
{
}

void Stage_Stage2::Init()
{
	stageOverTimer = 0;
	stageClearTimer = 0;
	bulletCount = 0;
	GameStateManager::GetSingleton().Init();
	Entity *newEntity;

#pragma region Texture
	TextureManager& tm = TextureManager::GetSingleton();
	tm.Add(T_BACKGROUND_1);
	tm.Add(T_BACKGROUND_2);
	tm.Add(T_BACKGROUND_3);
	tm.Add(T_BACKGROUND_4);
	tm.Add(T_BACKGROUND_5);
	tm.Add(T_ENEMY_1);
	tm.Add(T_ENEMY_2);
	tm.Add(T_ENEMY_3);
	tm.Add(T_ENEMY_BOSS);
	tm.Add(T_EXPLOSION);
	tm.Add(T_EXPLOSION_BIG);
	tm.Add(T_PLAYER);
	tm.Add(T_PLAYER_ADDON);
	tm.Add(T_BULLET);
	tm.Add(T_BULLET_ENEMY);
	tm.Add(T_BULLET_2);
	tm.Add(T_BULLET2_EXPLOSION);
	tm.Add(T_BULLET_SHELL);
	tm.Add(T_BULLET_EXPLOSION);
	tm.Add(T_UI_BACKGROUND_1);
	tm.Add(T_UI_BACKGROUND_2);
	tm.Add(T_UI_BAR_HEALTH);
	tm.Add(T_UI_BAR_EXP);
	tm.Add(T_UI_SHOP_POWER);
	tm.Add(T_UI_SHOP_MORESPEED);
	tm.Add(T_UI_SHOP_SPEED);
	tm.Add(T_UI_SHOP_ADDON);
	tm.Add(T_UI_SHOP_WEAPON);
	tm.Add(T_UI_BAR_BOSS);
	tm.Add(T_UI_BAR_BOSS_BG);
	tm.Add(T_UI_BAR_BOSS_BG_BLACK);
	tm.Add(T_UI_CLEAR);
	tm.Add(T_UI_GAMEOVER);
	tm.Add(T_HP);
	tm.Init();
#pragma endregion Texture
#pragma region Background
	newEntity = new Entity(T_BACKGROUND_1, 800, 600);
	newEntity->SetPos(0, 0);
	entities.push_back(newEntity);

	newEntity = new Entity(T_BACKGROUND_2, 1600, 600);
	newEntity->SetPos(0, 0);
	newEntity->Params["Type"] = "ScrollingBackground";
	newEntity->SetSpeed(-150, 0, 0, 0);
	entities.push_back(newEntity);

	newEntity = new Entity(T_BACKGROUND_3, 1600, 600);
	newEntity->SetPos(0, 0);
	newEntity->Params["Type"] = "ScrollingBackground";
	newEntity->SetSpeed(-200, 0, 0, 0);
	entities.push_back(newEntity);

	newEntity = new Entity(T_BACKGROUND_4, 1600, 600);
	newEntity->SetPos(0, 0);
	newEntity->Params["Type"] = "ScrollingBackground";
	newEntity->SetSpeed(-250, 0, 0, 0);
	entities.push_back(newEntity);

	newEntity = new Entity(T_BACKGROUND_5, 1600, 600);
	newEntity->SetPos(0, 0);
	newEntity->Params["Type"] = "ScrollingBackground";
	newEntity->SetSpeed(-300, 0, 0, 0);
	entities.push_back(newEntity);
#pragma endregion Background
#pragma region Player
	AddNewPlayer();

	Animation *newAddon = new Animation(T_PLAYER_ADDON, 150, 17, 1, 6);
	newAddon->Params["Type"] = "PlayerAddon";
	newAddon->Params["Name"] = "AddonUpper";
	newAddon->Play(30.0f, true);
	entities.push_back(newAddon);

	newAddon = new Animation(T_PLAYER_ADDON, 150, 17, 1, 6);
	newAddon->Params["Type"] = "PlayerAddon";
	newAddon->Params["Name"] = "AddonLower";
	newAddon->Play(30.0f, true);
	entities.push_back(newAddon);
#pragma endregion Player
#pragma region Enemy
	NpcManager& npcManager = NpcManager::GetSingleton();
	npcManager.RespawnTime = 2.5;
	npcManager.Init(&entities);
	Enemy *newEnemy = new Enemy(T_ENEMY_1, 503, 115, 2, 6);
	newEnemy->SetSpeed(-100, 0, 0, 0);
	newEnemy->Params["Name"] = "EnemyPlane";
	newEnemy->Params["EnemyType"] = "1";
	newEnemy->Params["Collide"] = "Player";
	SetRect(&newEnemy->HitMod, 0, -20, 0, 20);
	npcManager.Add(newEnemy);

	newEnemy = new Enemy(T_ENEMY_2, 503, 115, 2, 6);
	newEnemy->SetSpeed(-100, 0, 0, 0);
	newEnemy->Params["Name"] = "EnemyPlane";
	newEnemy->Params["EnemyType"] = "2";
	newEnemy->Params["Collide"] = "Player";
	SetRect(&newEnemy->HitMod, 0, -20, 0, 20);
	npcManager.Add(newEnemy);
#pragma endregion Enemy
#pragma region Animation
	AnimationAdder &animAddr = AnimationAdder::GetSingleton();
	animAddr.Init(&entities);
	Animation *newAnimation = new Animation(T_BULLET, 267, 12, 1, 5);
	newAnimation->Params["Type"] = "Player";
	newAnimation->Params["Name"] = "PlayerBullet";
	newAnimation->Play(20.0f, true);
	newAnimation->SetSpeed(280, 0, 0, 0);
	newAnimation->Health = 1;
	newAnimation->Power = 25;
	newAnimation->AutoRemove = true;
	animAddr.Add("PlayerBullet", newAnimation);

	newAnimation = new Animation(T_BULLET, 267, 12, 1, 5);
	newAnimation->Params["Type"] = "Player";
	newAnimation->Params["Name"] = "PlayerAddonBullet";
	newAnimation->Play(20.0f, true);
	newAnimation->SetSpeed(280, 0, 0, 0);
	newAnimation->Health = 1;
	newAnimation->Power = 10;
	newAnimation->AutoRemove = true;
	animAddr.Add("PlayerAddonBullet", newAnimation);

	newAnimation = new Animation(T_BULLET_2, 262, 13, 1, 6);
	newAnimation->Params["Type"] = "Player";
	newAnimation->Params["Name"] = "PlayerBullet2";
	newAnimation->Play(20.0f, true);
	newAnimation->SetSpeed(300, 0, 0, 0);
	newAnimation->Health = 1;
	newAnimation->Power = 50;
	newAnimation->AutoRemove = true;
	animAddr.Add("PlayerBullet2", newAnimation);

	newAnimation = new Animation(T_BULLET_ENEMY, 267, 12, 1, 5);
	newAnimation->Params["Collide"] = "Player";
	newAnimation->Params["Name"] = "EnemyBullet";
	newAnimation->Play(20.0f, true);
	newAnimation->Health = 15;
	newAnimation->Power = 25;
	newAnimation->AutoRemove = true;
	animAddr.Add("EnemyBullet", newAnimation);

	newAnimation = new Animation(T_BULLET_EXPLOSION, 90, 30, 1, 3);
	newAnimation->Play(20.0f, false);
	newAnimation->Params["DeleteWhenEnds"] = "True";
	animAddr.Add("BulletCrash", newAnimation);

	newAnimation = new Animation(T_BULLET2_EXPLOSION, 90, 30, 1, 3);
	newAnimation->Play(20.0f, false);
	newAnimation->Params["DeleteWhenEnds"] = "True";
	animAddr.Add("BulletCrash2", newAnimation);


	newAnimation = new Animation(T_EXPLOSION_BIG, 1200, 200, 1, 6);
	newAnimation->Play(10.0f, false);
	newAnimation->Params["DeleteWhenEnds"] = "True";
	animAddr.Add("Explosion_Big", newAnimation);

	newAnimation = new Animation(T_EXPLOSION, 1200, 200, 1, 6);
	newAnimation->Play(20.0f, false);
	newAnimation->Params["DeleteWhenEnds"] = "True";
	animAddr.Add("Explosion", newAnimation);

#pragma endregion Animation
#pragma region Particle
	ParticleAdder& particleAdder = ParticleAdder::GetSingleton();
	particleAdder.Init(&entities);
	Particle *newParticle = new Particle(T_BULLET_SHELL, 15, 5);
	particleAdder.Add("BulletShell", newParticle);
#pragma endregion Particle
#pragma region UI
	newEntity = new Entity(T_UI_BACKGROUND_1, 800, 600);
	newEntity->SetPos(0, 0);
	newEntity->Params["DrawLater"] = "True";
	entities.push_back(newEntity);

	newEntity = new Entity(T_UI_BAR_HEALTH, 160, 19);
	newEntity->SetPos(30, 530);
	newEntity->Params["Name"] = "Bar_Health";
	newEntity->Params["DrawLater"] = "True";
	entities.push_back(newEntity);

	newEntity = new Entity(T_UI_BAR_EXP, 160, 19);
	newEntity->SetPos(30, 556);
	newEntity->Params["Name"] = "Bar_Exp";
	newEntity->Params["DrawLater"] = "True";
	newEntity->Width = 0;
	entities.push_back(newEntity);

	newEntity = new Entity(T_UI_BAR_BOSS_BG_BLACK, 800, 600);
	newEntity->SetPos(800, 0);
	newEntity->Params["Name"] = "Bar_Boss_BG";
	newEntity->Params["DrawLater"] = "True";
	entities.push_back(newEntity);

	newEntity = new Entity(T_UI_BAR_BOSS, 709, 21);
	newEntity->SetPos(845, 80);
	newEntity->Params["Name"] = "Bar_Boss";
	newEntity->Params["DrawLater"] = "True";

	entities.push_back(newEntity);

	newEntity = new Entity(T_UI_BAR_BOSS_BG, 800, 600);
	newEntity->SetPos(800, 0);
	newEntity->Params["Name"] = "Bar_Boss_BG";
	newEntity->Params["DrawLater"] = "True";
	entities.push_back(newEntity);

	newAnimation = new Animation(T_UI_SHOP_POWER, 600, 50, 1, 6);
	newAnimation->SetPos(335, 528);
	newAnimation->Params["Type"] = "ShopItem";
	newAnimation->Params["Name"] = "Shop_Power";
	newAnimation->Params["DrawLater"] = "True";
	entities.push_back(newAnimation);

	newAnimation = new Animation(T_UI_SHOP_SPEED, 600, 50, 1, 6);
	newAnimation->SetPos(430, 528);
	newAnimation->Params["Type"] = "ShopItem";
	newAnimation->Params["Name"] = "Shop_Speed";
	newAnimation->Params["DrawLater"] = "True";
	entities.push_back(newAnimation);

	newAnimation = new Animation(T_UI_SHOP_MORESPEED, 600, 50, 1, 6);
	newAnimation->SetPos(516, 528);
	newAnimation->Params["Type"] = "ShopItem";
	newAnimation->Params["Name"] = "Shop_MoreSpeed";
	newAnimation->Params["DrawLater"] = "True";
	entities.push_back(newAnimation);

	newAnimation = new Animation(T_UI_SHOP_ADDON, 600, 50, 1, 6);
	newAnimation->SetPos(602, 528);
	newAnimation->Params["Type"] = "ShopItem";
	newAnimation->Params["Name"] = "Shop_Addon";
	newAnimation->Params["DrawLater"] = "True";
	entities.push_back(newAnimation);

	newAnimation = new Animation(T_UI_SHOP_WEAPON, 600, 50, 1, 6);
	newAnimation->SetPos(694, 528);
	newAnimation->Params["Type"] = "ShopItem";
	newAnimation->Params["Name"] = "Shop_Weapon";
	newAnimation->Params["DrawLater"] = "True";
	entities.push_back(newAnimation);

	newEntity = new Entity(T_UI_BACKGROUND_2, 800, 600);
	newEntity->SetPos(0, 0);
	newEntity->Params["DrawLater"] = "True";
	entities.push_back(newEntity);

	Font *newFont = new Font(L"Candara", 190, 40, 40, 15, FW_BOLD, false);
	newFont->SetPos(90, -3);
	newFont->Params["DrawLater"] = "True";
	newFont->Params["Name"] = "Text_Score";
	newFont->SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
	entities.push_back(newFont);

	newFont = new Font(L"Candara", 35, 40, 40, 15, FW_BOLD, false);
	newFont->SetPos(260, 540);
	newFont->Params["DrawLater"] = "True";
	newFont->Params["Name"] = "Text_Level";
	newFont->SetColor(D3DCOLOR_ARGB(255, 255, 255, 0));
	entities.push_back(newFont);

	newEntity = new Entity(T_HP, 42, 33);
	newEntity->SetPos(10, 470);
	newEntity->Params["DrawLater"] = "True";
	entities.push_back(newEntity);

	newFont = new Font(L"Candara", 40, 40, 40, 15, FW_BOLD, false);
	newFont->SetPos(60, 465);
	newFont->Params["DrawLater"] = "True";
	newFont->Params["Text"] = "x";
	newFont->SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
	entities.push_back(newFont);

	newFont = new Font(L"Candara", 40, 40, 40, 15, FW_BOLD, false);
	newFont->SetPos(80, 465);
	newFont->Params["DrawLater"] = "True";
	newFont->Params["Name"] = "Text_Life";
	newFont->SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
	entities.push_back(newFont);

	newEntity = new Entity(T_UI_CLEAR, 800, 600);
	newEntity->SetPos(800, 0);
	newEntity->Params["Name"] = "Text_Clear";
	newEntity->Params["DrawLater"] = "True";
	entities.push_back(newEntity);

	newEntity = new Entity(T_UI_GAMEOVER, 800, 600);
	newEntity->SetPos(800, 0);
	newEntity->Params["Name"] = "Text_Over";
	newEntity->Params["DrawLater"] = "True";
	entities.push_back(newEntity);

#pragma endregion UI
}

void Stage_Stage2::AddNewPlayer()
{
	if ( GameStateManager::GetSingleton().State["Life"] != 0 )
	{
		Player *player = new Player(T_PLAYER, 503, 115, 2, 6);
		player->SetPos(-200, 250);
		player->Health = 100;
		player->Params["Type"] = "Player";
		SetRect(&player->HitMod, 0, -20, 0, 10);
		player->Params["Name"] = "PlayerPlane";
		player->Params["Collide"] = "Item";
		entities.push_back(player);
	}
	else
	{
		GameStateManager::GetSingleton().State["GameOver"] = 1;
	}
}

void Stage_Stage2::Update(float deltaTime)
{
	SoundManager::GetSingleton().PlayLoop("BGM2");
	NpcManager& npcManager = NpcManager::GetSingleton();
	GameStateManager& gameState = GameStateManager::GetSingleton();
	KeyboardManager& keyboard = KeyboardManager::GetSingleton();

	if ( keyboard.IsKeyPressedN(VK_ESCAPE) )
	{
		StageManager::GetSingleton().NextStage = "Menu";
	}
#pragma region Debug Keys
	else if ( keyboard.IsKeyPressedN(VK_F1) )
	{
		gameState.State["Exp"] = gameState.State["NextExp"];
	}
	else if ( keyboard.IsKeyPressedN(VK_F2) )
	{
		gameState.State["Score"] += 100000;
	}
#pragma endregion Debug Keys
#pragma region Shop System
	if ( keyboard.IsKeyPressedN('1') && gameState.State["Score"] >= gameState.State["Shop_Power"] && gameState.State["Power"] != 1)
	{
		gameState.State["Score"] -= gameState.State["Shop_Power"];
		gameState.State["Power"]++;
	}
	else if ( keyboard.IsKeyPressedN('2') && gameState.State["Score"] >= gameState.State["Shop_Speed"] )
	{
		gameState.State["Score"] -= gameState.State["Shop_Speed"];
		gameState.State["Speed"]++;
	}
	else if ( keyboard.IsKeyPressedN('3') && gameState.State["Score"] >= gameState.State["Shop_MoreSpeed"] )
	{
		gameState.State["Score"] -= gameState.State["Shop_MoreSpeed"];
		gameState.State["Speed"] += 5;
	}
	else if ( keyboard.IsKeyPressedN('4') && gameState.State["Score"] >= gameState.State["Shop_Addon"] && gameState.State["Addon"] != 2 )
	{
		gameState.State["Score"] -= gameState.State["Shop_Addon"];
		gameState.State["Addon"]++;
	}
	else if ( keyboard.IsKeyPressedN('5') && gameState.State["Score"] >= gameState.State["Shop_Weapon"] && gameState.State["Weapon"] != 1 )
	{
		gameState.State["Score"] -= gameState.State["Shop_Weapon"];
		gameState.State["Power"] = 0;
		gameState.State["Weapon"]++;
	}
#pragma endregion Shop System
#pragma region Solid State Squad
	if ( gameState.State["Clear"] == 1 )
	{
		stageClearTimer += deltaTime;
		NpcManager::GetSingleton().RespawnTime = 99999;
		if ( stageClearTimer > 5 )
			StageManager::GetSingleton().NextStage = "Stage3";
	}
	if ( gameState.State["GameOver"] == 1 )
	{
		stageOverTimer += deltaTime;
		NpcManager::GetSingleton().RespawnTime = 99999;
		if ( stageOverTimer > 5 )
			keyboard.Update(VK_ESCAPE, true);
	}
	if ( gameState.State["1up"] == 1 )
	{
		Enemy *newEnemy;
		newEnemy = new Enemy(T_ENEMY_3, 503, 115, 2, 6);
		newEnemy->SetSpeed(-100, 0, 0, 0);
		newEnemy->SetPos((float)800, Helper::Random(0, 45) * 10.0f);
		newEnemy->Health = 200;
		newEnemy->Params["Name"] = "EnemyPlane";
		newEnemy->Params["EnemyType"] = "3";
		newEnemy->Params["Collide"] = "Player";
		SetRect(&newEnemy->HitMod, 0, -20, 0, 20);
		entities.push_back(newEnemy);
		gameState.State["1up"] = 0;
	}
	if ( gameState.State["Level"] == 16 && gameState.State["Boss"] != 1 )
	{
		EnemyBoss *bossTest = new EnemyBoss(T_ENEMY_BOSS, 539, 129, 1, 1);
		bossTest->SetPos(800, 150);
		bossTest->Params["Name"] = "Boss";
		bossTest->Params["BossType"] = "2";
		bossTest->Params["Collide"] = "Player";
		bossTest->Health = 3000;
		bossTest->Power = 10000;
		SetRect(&bossTest->HitMod, -20, 0, 0, 0);
		entities.push_back(bossTest);
		npcManager.RespawnTime = 5;
		gameState.State["Boss"] = 1;
	}
#pragma endregion LED

	npcManager.RespawnTimeMod = gameState.State["Level"] * 0.12f;
	npcManager.Update(deltaTime);
	gameState.Update(deltaTime);
	Stage::Update(deltaTime);
}

void Stage_Stage2::UpdateEntities(Entity *entity, float deltaTime)
{

	Animation *anim;
	Particle *part;

	GameStateManager& gameState = GameStateManager::GetSingleton();
	AnimationAdder& animAddr = AnimationAdder::GetSingleton();
	ParticleAdder& particleAddr = ParticleAdder::GetSingleton();
#pragma region Scrollingbackground
	if ( entity->Params["Type"] == "ScrollingBackground" )
	{
		//entity->XSpeedEmergencyModder = gameState.State["Speed"] * -50.0f;
		if ( entity->X <= -800 )
		{
			entity->X += 800;
		}
	}
#pragma endregion WEEEEEEEEE
#pragma region ShopItem
	else if ( entity->Params["Type"] == "ShopItem" )
	{
		if ( gameState.State["Score"] >= gameState.State[entity->Params["Name"]] )
		{
			((Animation*)entity)->Play(10.0f, false);
		}
		else
		{
			((Animation*)entity)->Play(-10.0f, false);
		}

		if ( entity->Params["Name"] == "Shop_Power" && gameState.State["Power"] == 1 )
		{
			entity->Y = 600;
		}
		else if ( entity->Params["Name"] == "Shop_Power" )
		{
			entity->Y = 528;
		}
		else if ( entity->Params["Name"] == "Shop_Weapon" && gameState.State["Weapon"] == 1 )
		{
			entity->Y = 600;
		}
		else if ( entity->Params["Name"] == "Shop_Weapon" )
		{
			entity->Y = 528;
		}
		else if ( entity->Params["Name"] == "Shop_Addon" && gameState.State["Addon"] == 2 )
		{
			entity->Y = 600;
		}
		else if ( entity->Params["Name"] == "Shop_Addon" )
		{
			entity->Y = 528;
		}
	}
#pragma endregion ShopItem
#pragma region PlayerAddon
	else if ( entity->Params["Type"] == "PlayerAddon" )
	{

		if ( entity->Params["Name"] == "AddonUpper" )
		{
			if ( gameState.State["Addon"] >= 2 )
			{
				entity->SetPos((float)gameState.State["PlayerX"], (float)gameState.State["PlayerY"] - 15);
			}
			else
			{
				entity->SetPos((float)-13371337, (float)-13371337);
			}
		}
		else if ( entity->Params["Name"] == "AddonLower" )
		{
			if ( gameState.State["Addon"] >= 1 )
			{
				entity->SetPos((float)gameState.State["PlayerX"], (float)gameState.State["PlayerY"] + 50);
			}
			else
			{
				entity->SetPos((float)-13371337, (float)-13371337);
			}
		}
	}
#pragma endregion Player Addons!
#pragma region PlayerPlane
	if ( entity->Params["Name"] == "PlayerPlane" )
	{
		entity->Params["Switching"] = "";
		gameState.State["Health"] = entity->Health;
		((Player*)entity)->MoveSpeedMod = gameState.State["Speed"] * 10.0f;
		gameState.State["PlayerX"] = (int)entity->X;
		gameState.State["PlayerY"] = (int)entity->Y;

		if ( entity->Params["OnFire"] == "True" )
		{
			if ( bulletCount < MAX_BULLETS )
			{

				if ( gameState.State["Power"] >= 1 )
				{
					if ( gameState.State["Weapon"] < 1 )
					{
						anim = animAddr.Prepare("PlayerBullet");
						anim->SetPos(entity->X + entity->Width - 25, entity->Y + entity->Height / 2 - 20);
						animAddr.Fire();

						anim = animAddr.Prepare("PlayerBullet");
						anim->SetPos(entity->X + entity->Width - 25, entity->Y + entity->Height / 2 - 10);
						animAddr.Fire();
					}
					else
					{
						anim = animAddr.Prepare("PlayerBullet2");
						anim->SetPos(entity->X + entity->Width - 25, entity->Y + entity->Height / 2 + 5);
						animAddr.Fire();

						anim = animAddr.Prepare("PlayerBullet2");
						anim->SetPos(entity->X + entity->Width - 25, entity->Y + entity->Height / 2);
						animAddr.Fire();
					}
				}
				else
				{
					if ( gameState.State["Weapon"] < 1 )
					{
						anim = animAddr.Prepare("PlayerBullet");
						anim->SetPos(entity->X + entity->Width - 25, entity->Y + entity->Height / 2 + 5);
						animAddr.Fire();
					}
					else
					{
						anim = animAddr.Prepare("PlayerBullet2");
						anim->SetPos(entity->X + entity->Width - 25, entity->Y + entity->Height / 2 + 5);
						animAddr.Fire();
					}
				}

				if ( gameState.State["Addon"] >= 1 )
				{
					anim = animAddr.Prepare("PlayerAddonBullet");
					anim->SetPos(entity->X + 27, entity->Y + 50);
					animAddr.Fire();
				}
				if ( gameState.State["Addon"] >= 2 )
				{
					anim = animAddr.Prepare("PlayerAddonBullet");
					anim->SetPos(entity->X + 27, entity->Y - 15);
					animAddr.Fire();
				}

				part = particleAddr.Prepare("BulletShell");
				part->SetPos(entity->X + entity->Width - 25, entity->Y + entity->Height / 2 - 10);
				part->RotSpeed = (float)Helper::Random(15, 30);
				part->SetSpeed((float)-Helper::Random(50, 90), (float)130, (float)-Helper::Random(100, 200), (float)Helper::Random(200, 300));
				particleAddr.Fire();
				SoundManager::GetSingleton().Play("Shoot");
				bulletCount++;
			}
		}
		if ( entity->Params["Crashed"] == "True" )
		{
			SoundManager::GetSingleton().Play("Explode");
			anim = animAddr.Prepare("Explosion");
			anim->SetPos(entity->X - 50, entity->Y - 60);
			animAddr.Fire();
			gameState.State["Score"] -= 10000;
			gameState.State["Life"]--;
			gameState.InitWeapons();
			AddNewPlayer();

			entity->Params["Delete"] = "True";
		}
	}
#pragma endregion PlayerPlane, and shootin mah bullets
#pragma region EnemyPlane
	else if ( entity->Params["Name"] == "EnemyPlane" )
	{
		if ( entity->Params["EnemyType"] == "1" )
		{
			if ( entity->Params["Crashed"] == "True" )
			{
				SoundManager::GetSingleton().Play("Explode");
				anim = animAddr.Prepare("Explosion");
				anim->SetPos(entity->X - 60, entity->Y - 60);
				animAddr.Fire();
				gameState.State["Score"] += 1000;
				gameState.State["Exp"] += 500;
				entity->Params["Delete"] = "True";
			}
		}
		else if ( entity->Params["EnemyType"] == "2" )
		{
			if ( entity->Params["Crashed"] == "True" )
			{
				SoundManager::GetSingleton().Play("Explode");
				anim = animAddr.Prepare("Explosion");
				anim->SetPos(entity->X - 60, entity->Y - 60);
				animAddr.Fire();
				gameState.State["Score"] += 5000;
				gameState.State["Exp"] += 650;
				entity->Params["Delete"] = "True";
			}
			if ( entity->Params["OnFire"] == "True" )
			{
				anim = animAddr.Prepare("EnemyBullet");
				anim->SetPos(entity->X + 15, entity->Y + entity->Height / 2 - 10);
				anim->SetSpeed(-350, 0, 0, 0);
				animAddr.Fire();
			}
		}
		else if ( entity->Params["EnemyType"] == "3" )
		{
			if ( entity->Params["Crashed"] == "True" )
			{
				SoundManager::GetSingleton().Play("Explode");
				anim = animAddr.Prepare("Explosion");
				anim->SetPos(entity->X - 60, entity->Y - 60);
				animAddr.Fire();

				Entity *newEntity = new Entity(T_HP, 42, 33);
				newEntity->SetPos(entity->X, entity->Y);
				newEntity->SetSpeed(-230, 0, 0, 0);
				newEntity->Params["Type"] = "Item";
				newEntity->Params["Name"] = "UP";
				newEntity->Power = 0;
				newEntity->Health = 1;
				entities.push_back(newEntity);

				gameState.State["Score"] += 10000;
				gameState.State["Exp"] += 1000;
				entity->Params["Delete"] = "True";
			}
		}
	}
#pragma endregion EnemyPlane
#pragma region PlayerBullet
	else if ( entity->Params["Name"] == "PlayerBullet" )
	{
		if ( entity->Params["Crashed"] == "True" )
		{
			Animation *anim = animAddr.Prepare("BulletCrash");
			anim->SetPos(entity->X, entity->Y);
			animAddr.Fire();
			entity->Params["Delete"] = "True";
		}
		if ( entity->Params["Delete"] == "True" )
		{
			bulletCount--;
		}
	}
	else if ( entity->Params["Name"] == "PlayerBullet2" )
	{
		if ( entity->Params["Crashed"] == "True" )
		{
			Animation *anim = animAddr.Prepare("BulletCrash2");
			anim->SetPos(entity->X, entity->Y);
			animAddr.Fire();
			entity->Params["Delete"] = "True";
		}
		if ( entity->Params["Delete"] == "True" )
		{
			bulletCount--;
		}
	}
#pragma endregion PlayerBullet
#pragma region PlayerAddonBullet
	else if ( entity->Params["Name"] == "PlayerAddonBullet" )
	{
		if ( entity->Params["Crashed"] == "True" )
		{
			Animation *anim = animAddr.Prepare("BulletCrash");
			anim->SetPos(entity->X, entity->Y);
			animAddr.Fire();
			entity->Params["Delete"] = "True";
		}
	}
#pragma endregion PlayerAddonBullet
#pragma region EnemyBullet
	else if ( entity->Params["Name"] == "EnemyBullet" )
	{
		if ( entity->Params["Crashed"] == "True" )
		{
			Animation *anim = animAddr.Prepare("BulletCrash");
			anim->SetPos(entity->X, entity->Y);
			animAddr.Fire();
			entity->Params["Delete"] = "True";
		}
	}
#pragma endregion Enemy Bullet!
#pragma region Boss
	else if ( entity->Params["Name"] == "Boss" )
	{
		gameState.State["BossHealth"] = entity->Health;
		if ( entity->Params["OnFire"] == "True" )
		{
			anim = animAddr.Prepare("EnemyBullet");
			anim->SetPos(entity->X + 30, entity->Y + 19);
			anim->SetSpeed(-350, 0, 0, 0);
			animAddr.Fire();

			anim = animAddr.Prepare("EnemyBullet");
			anim->SetPos(entity->X + 30, entity->Y + 43);
			anim->SetSpeed(-350, 0, 0, 0);
			animAddr.Fire();

			anim = animAddr.Prepare("EnemyBullet");
			anim->SetPos(entity->X + 30, entity->Y + 79);
			anim->SetSpeed(-350, 0, 0, 0);
			animAddr.Fire();
		}
		if ( entity->Params["OnDamaged"] == "True" )
		{
			gameState.State["Score"] += 100;
			gameState.State["Exp"] += 80;
		}

		if ( entity->Params["Crashed"] == "True" )
		{
			SoundManager::GetSingleton().Play("Explode");
			gameState.State["Clear"] = 1;
			anim = animAddr.Prepare("Explosion_Big");
			anim->SetPos(entity->X - 60, entity->Y - 60);
			animAddr.Fire();
			entity->Params["Delete"] = "True";
		}
	}
#pragma endregion Boss
#pragma region UI
	else if ( entity->Params["Name"] == "Bar_Health" )
	{
		entity->Width = entity->TextureWidth * gameState.State["Health"] / gameState.State["MaxHealth"];
	}
	else if ( entity->Params["Name"] == "Bar_Exp" )
	{
		entity->Width = entity->TextureWidth * gameState.State["Exp"] / gameState.State["NextExp"];
	}
	else if ( entity->Params["Name"] == "Text_Score" )
	{
		entity->Params["Text"] = gameState.GetStateString("Score");
	}
	else if ( entity->Params["Name"] == "Text_Level" )
	{
		entity->Params["Text"] = gameState.GetStateString("Level");
	}
	else if ( entity->Params["Name"] == "Text_Life" )
	{
		entity->Params["Text"] = gameState.GetStateString("Life");
	}
	else if ( entity->Params["Name"] == "Bar_Boss" )
	{
		if ( gameState.State["Boss"] != 1 )
			entity->X = 800;
		else
		{
			entity->X = 320;
			entity->Y = 10;
			entity->Width = entity->TextureWidth * gameState.State["BossHealth"] / gameState.State["BossMaxHealth"];
		}
	}
	else if ( entity->Params["Name"] == "Bar_Boss_BG" )
	{
		if ( gameState.State["Boss"] != 1 )
			entity->X = 800;
		else
			entity->X = 0;
	}
	else if ( entity->Params["Name"] == "Text_Clear" )
	{
		if ( gameState.State["Clear"] == 1 )
		{
			entity->X = 0;
		}
	}
	else if ( entity->Params["Name"] == "Text_Over" )
	{
		if ( gameState.State["GameOver"] == 1 )
		{
			entity->X = 0;
		}
	}
#pragma endregion Do the rest of UI elements
	else if ( entity->Params["Name"] == "UP" )
	{

		if ( entity->Params["Crashed"] == "True" )
		{
			gameState.State["Life"]++;
			entity->Params["Delete"] = "True";
		}
	}
	if ( entity->Params["Collide"] != "" )
		CollisionCheck(entity);

	Stage::UpdateEntities(entity, deltaTime);
}

void Stage_Stage2::CollisionCheck(Entity *entity)
{

	list<Entity*>::iterator it;

	for ( it = entities.begin(); it != entities.end(); ++it )
	{
		if ( (*it)->Params["Type"] == entity->Params["Collide"] && Helper::HitTest(entity->HitRect, (*it)->HitRect) )
			OnCollide(entity, *it);
	}
}

void Stage_Stage2::OnCollide(Entity *a, Entity *b)
{

	if ( a->Params["Crashed"] != "True" && b->Params["Crashed"] != "True" )
	{
		a->Damage = b->Power;
		b->Damage = a->Power;
	}
}

void Stage_Stage2::Release()
{
	TextureManager::GetSingleton().Release();
	NpcManager::GetSingleton().Release();
	AnimationAdder::GetSingleton().Release();
	ParticleAdder::GetSingleton().Release();
	Stage::Release();
}
