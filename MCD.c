#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_CHARACTERS_TO_READ 100

#define NO_WEAPON_DAMAGE 1
#define WOODEN_SWORD_DAMAGE 4
#define STONE_SWORD_DAMAGE 5
#define IRON_SWORD_DAMAGE 6
#define DIAMOND_SWORD_DAMAGE 7

#define MAX_SHARPNESS_ENCHANT_LEVEL 9999
#define MIN_SHARPNESS_ENCHANT_LEVEL 0
#define MAX_STRENGTH_LEVEL 127
#define MIN_STRENGTH_LEVEL 0
#define MAX_SELECTED_ENEMY 7
#define MIN_SELECTED_ENEMY 0
#define MAX_SELECTED_ARMOR 5
#define MIN_SELECTED_ARMOR 0
#define MAX_ENCHANT_LEVEL 37000
#define MIN_ENCHANT_LEVEL 0

#define DISPLAY_WIDTH 70

#define DEBUG_SWITCH true

#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)

double Off=0,Deff=0;
double damage=0;
char yesNo;
int defenceValue = 0;//防御力
int armorStrength = 0;//防具強度

bool isExpectedInput(int min,int max,int value){
   if((min <= value)&&(value <= max))return true;
   else return false;
}

bool yesNoJ(){
   if(yesNo == 'y')return true;
   else return false;
}

void display(bool debag){
   system("cls");
   for(int i = 0;i < DISPLAY_WIDTH;i++)printf("■");
   printf("\n");
   printf("現在の攻撃力(Off)  : %5.1lf\n",Off);
   printf("現在の防御力(Deff) : ダメージ%5.1lf％カット\n",Deff);
   if(debag){
      printf("off:%lf\n",Off);
      printf("deff:%lf\n",Deff);
      printf("defence value:%d\n",defenceValue);
      printf("armor strength:%d\n",armorStrength);
      printf("(defenceValue/125):%lf\n",(defenceValue/125));
      printf("((defenceValue-(Off/(2+armorStrength/4)))/25):%lf\n",((defenceValue-(Off/(2+armorStrength/4)))/25));
   }
   for(int i = 0;i < DISPLAY_WIDTH;i++)printf("■");
   printf("\n");
}

int main(){
   display(DEBUG_SWITCH);


   //武器

   char selectedWeapon;
   bool isExpectedCharInput = 1;
   do{
      printf("メインウエポン：使用武器は？\n");
      printf("[素手=n,木の剣/金の剣=w,石剣=s,鉄剣=i,ダイヤ剣＝d]:");
      scanf(" %c",&selectedWeapon);
      if(selectedWeapon == 'n')Off += NO_WEAPON_DAMAGE;
      else if(selectedWeapon == 'w')Off += WOODEN_SWORD_DAMAGE;
      else if(selectedWeapon == 's')Off += STONE_SWORD_DAMAGE;
      else if(selectedWeapon == 'i')Off += IRON_SWORD_DAMAGE;
      else if(selectedWeapon == 'd')Off += DIAMOND_SWORD_DAMAGE;
      else isExpectedCharInput = 0;
   }while(isExpectedCharInput != 1);

   display(DEBUG_SWITCH);

   //武器エンチャント
   int sharpnessEnchantLevel = 0;
   if(selectedWeapon != 'n'){//素手ではない場合のみ実行
      do{
         printf("エンチャント：使用武器の「ダメージ増加」のエンチャントレベルは？\n");
         printf("[0~9999の整数値]:");
         scanf("%d",&sharpnessEnchantLevel);
      }while(!(isExpectedInput(MIN_SHARPNESS_ENCHANT_LEVEL , MAX_SHARPNESS_ENCHANT_LEVEL , sharpnessEnchantLevel)));
      Off += sharpnessEnchantLevel*0.5;
   }
   display(DEBUG_SWITCH);
   //攻撃力上昇ポーション
   double strengthLevel = 0;
   do{
      printf("エフェクト：攻撃力上昇のレベルは？\n");
      printf("[0~127の整数値]:");
      scanf("%lf",&strengthLevel);
   }while(!(isExpectedInput(MIN_STRENGTH_LEVEL,MAX_STRENGTH_LEVEL,strengthLevel)));
   Off += strengthLevel*0.5;

   display(DEBUG_SWITCH);

   //防御点-素

   short selectedEnemy = 0;
   do{
      printf("敵の種類を選んでください\n");
      printf("[ゾンビ,ゾンビピックマン,村人ゾンビ,ハスク,ドラウンド:1\nマグマキューブ（小:2\nウィザー:3\nマグマキューブ（中）:4\nマグマキューブ（大）:5\n殺人ウサギ:6\nシュルカー（殻を閉じている時）:7\nその他:0]:");
      scanf("%d",&selectedEnemy);
   }while(!(isExpectedInput(MIN_SELECTED_ENEMY,MAX_SELECTED_ENEMY,selectedEnemy)));
   switch (selectedEnemy){
   case 0:
      defenceValue += 0;
      break;
   case 1:
      defenceValue += 2;
      break;
   case 2:
      defenceValue += 3;
      break;
   case 3:
      defenceValue += 4;
      break;
   case 4:
      defenceValue += 6;
      break;
   case 5:
      defenceValue += 8;
      break;
   case 6:
      defenceValue += 12;
      break;
   case 7:
      defenceValue += 20;
      break;
   };

   display(DEBUG_SWITCH);

   //防御点-装備

   int selectedEnemyHelmet=0,
   selectedEnemyChestplate=0,
   selectedEnemyLeggins=0,
   selectedEnemyBoots=0;

   if(selectedEnemy <= 2){
      do{
         printf("敵の装備を指定してください\n");
         do{
            printf("ヘルメット[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&selectedEnemyHelmet);
         }while(!(isExpectedInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,selectedEnemyHelmet)));
         do{
            printf("チェストプレート[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&selectedEnemyChestplate);
         }while(!(isExpectedInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,selectedEnemyChestplate)));
         do{
            printf("レギンス[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&selectedEnemyLeggins);
         }while(!(isExpectedInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,selectedEnemyLeggins)));
         do{
            printf("ブーツ[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&selectedEnemyBoots);
         }while(!(isExpectedInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,selectedEnemyBoots)));
         printf("ヘルメット:%d\nチェストプレート:%d\nレギンス:%d\nブーツ:%d\n",selectedEnemyHelmet,selectedEnemyChestplate,selectedEnemyLeggins,selectedEnemyBoots);
         do{
            printf("これでよろしいでしょうか？[yes:y/no:n]");
            scanf(" %c",&yesNo);
         }while(!(yesNo == 'y' || yesNo == 'n'));
      }while(!(yesNoJ()));
   };
   //防御点-加算(ついでに防具強度計算)
   //Helmet
   switch(selectedEnemyHelmet){
      case 0:
         break;
      case 1:
         defenceValue += 1;
         break;
      case 2:
         defenceValue += 2;
         break;
      case 3:
         defenceValue += 2;
         break;
      case 4:
         defenceValue += 2;
         break;
      case 5:
         defenceValue += 3;
         armorStrength += 2;
         break;
   }
   //Chestplate
   switch(selectedEnemyChestplate){
      case 0:
         break;
      case 1:
         defenceValue += 3;
         break;
      case 2:
         defenceValue += 5;
         break;
      case 3:
         defenceValue += 5;
         break;
      case 4:
         defenceValue += 6;
         break;
      case 5:
         defenceValue += 8;
         armorStrength += 2;
         break;
   }
   //Leggins
   switch(selectedEnemyLeggins){
      case 0:
         break;
      case 1:
         defenceValue += 2;
         break;
      case 2:
         defenceValue += 3;
         break;
      case 3:
         defenceValue += 4;
         break;
      case 4:
         defenceValue += 5;
         break;
      case 5:
         defenceValue += 6;
         armorStrength += 2;
         break;
   }
   //Boots
   switch(selectedEnemyBoots){
      case 0:
         break;
      case 1:
         defenceValue += 1;
         break;
      case 2:
         defenceValue += 1;
         break;
      case 3:
         defenceValue += 1;
         break;
      case 4:
         defenceValue += 2;
         break;
      case 5:
         defenceValue += 3;
         armorStrength += 2;
         break;
   }

   display(DEBUG_SWITCH);
   //ダメージ軽減エンチャント

   int enchantLevel=0;
   do{
      printf("ダメージ軽減エンチャントの合計レベルを入力してください\n");
      printf("[0~200の整数値]:");
      scanf("%d",&enchantLevel);
      enchantLevel = enchantLevel>20?20:enchantLevel;
   }while(!(isExpectedInput(MIN_ENCHANT_LEVEL,MAX_ENCHANT_LEVEL,enchantLevel)));

   display(DEBUG_SWITCH);

   //計算フェイズ
   Deff=MAX((defenceValue/125),((defenceValue-(Off/(2+armorStrength/4)))/25));
   damage = (1-Deff) * Off;
   damage*= 1-(4*enchantLevel)/100;
   //終了処理
   display(DEBUG_SWITCH);
   printf("貴方が相手に与えられるダメージは %.8lf です\n",damage);



   getch();
   exit(0);
}
/*
ダメージ計算式
①ダメージ軽減割合＝(defenceValue-(Off÷(2+armorStrength÷4)))÷25
②ダメージ軽減割合＝defenceValue÷125
の高いほう

上記ダメージ割合と攻撃側の攻撃力を乗算して実ダメージを割り出せる。

③damage＝Deff×Off
エンチャントの処理

*/
