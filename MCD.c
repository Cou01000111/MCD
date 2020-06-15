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

char yesNo;

typedef struct{
   double offensivePower;
   double deffensivePower;
   int defenceValue;//防御力
   int armorStrength;//防具強度
   char selectedWeapon;
   double strengthLevel;
   int sharpnessEnchantLevel;
   short selectedEnemy;
   int selectedEnemyHelmet,
       selectedEnemyChestplate,
       selectedEnemyLeggins,
       selectedEnemyBoots;
   int weaponEnchantLevel;
   double damage;
}dataSet;

dataSet data = {0};


bool isExpectedInput(int min,int max,int value){//T
   if((min <= value)&&(value <= max))return true;
   else return false;
}

bool yesNoJ(){//T
   if(yesNo == 'y')return true;
   else return false;
}

void display(bool debag){//V
   system("cls");
   for(int i = 0;i < DISPLAY_WIDTH;i++)printf("■");
   printf("\n");
   printf("現在の攻撃力(data.offensivePower)  : %5.1lf\n",data.offensivePower);
   printf("現在の防御力(data.deffensivePower) : ダメージ%5.1lf％カット\n",data.deffensivePower);
   if(debag){
      printf("data.offensivePower:%lf\n",data.offensivePower);
      printf("data.deffensivePower:%lf\n",data.deffensivePower);
      printf("defence value:%d\n",data.defenceValue);
      printf("armor strength:%d\n",data.armorStrength);
      printf("(data.defenceValue/125):%lf\n",(data.defenceValue/125));
      printf("((data.defenceValue-(data.offensivePower/(2+data.armorStrength/4)))/25):%lf\n",((data.defenceValue-(data.offensivePower/(2+data.armorStrength/4)))/25));
   }
   for(int i = 0;i < DISPLAY_WIDTH;i++)printf("■");
   printf("\n");
}

int main(){
   display(DEBUG_SWITCH);


   //武器
   bool isExpectedCharInput = 1;
   do{
      printf("メインウエポン：使用武器は？\n");
      printf("[素手=n,木の剣/金の剣=w,石剣=s,鉄剣=i,ダイヤ剣＝d]:");
      scanf(" %c",&data.selectedWeapon);
      if(data.selectedWeapon == 'n')data.offensivePower += NO_WEAPON_DAMAGE;
      else if(data.selectedWeapon == 'w')data.offensivePower += WOODEN_SWORD_DAMAGE;
      else if(data.selectedWeapon == 's')data.offensivePower += STONE_SWORD_DAMAGE;
      else if(data.selectedWeapon == 'i')data.offensivePower += IRON_SWORD_DAMAGE;
      else if(data.selectedWeapon == 'd')data.offensivePower += DIAMOND_SWORD_DAMAGE;
      else isExpectedCharInput = 0;
   }while(isExpectedCharInput != 1);

   display(DEBUG_SWITCH);

   //武器エンチャント
   if(data.selectedWeapon != 'n'){//素手ではない場合のみ実行
      do{
         printf("エンチャント：使用武器の「ダメージ増加」のエンチャントレベルは？\n");
         printf("[0~9999の整数値]:");
         scanf("%d",&data.sharpnessEnchantLevel);
      }while(!(isExpectedInput(MIN_SHARPNESS_ENCHANT_LEVEL , MAX_SHARPNESS_ENCHANT_LEVEL , data.sharpnessEnchantLevel)));
      data.offensivePower += data.sharpnessEnchantLevel*0.5;
   }
   display(DEBUG_SWITCH);
   //攻撃力上昇ポーション

   do{
      printf("エフェクト：攻撃力上昇のレベルは？\n");
      printf("[0~127の整数値]:");
      scanf("%lf",&data.strengthLevel);
   }while(!(isExpectedInput(MIN_STRENGTH_LEVEL,MAX_STRENGTH_LEVEL,data.strengthLevel)));
   data.offensivePower += data.strengthLevel*0.5;

   display(DEBUG_SWITCH);

   //防御点-素

   do{
      printf("敵の種類を選んでください\n");
      printf("[ゾンビ,ゾンビピックマン,村人ゾンビ,ハスク,ドラウンド:1\nマグマキューブ（小:2\nウィザー:3\nマグマキューブ（中）:4\nマグマキューブ（大）:5\n殺人ウサギ:6\nシュルカー（殻を閉じている時）:7\nその他:0]:");
      scanf("%d",&data.selectedEnemy);
   }while(!(isExpectedInput(MIN_SELECTED_ENEMY,MAX_SELECTED_ENEMY,data.selectedEnemy)));
   switch (data.selectedEnemy){
   case 0:
      data.defenceValue += 0;
      break;
   case 1:
      data.defenceValue += 2;
      break;
   case 2:
      data.defenceValue += 3;
      break;
   case 3:
      data.defenceValue += 4;
      break;
   case 4:
      data.defenceValue += 6;
      break;
   case 5:
      data.defenceValue += 8;
      break;
   case 6:
      data.defenceValue += 12;
      break;
   case 7:
      data.defenceValue += 20;
      break;
   };

   display(DEBUG_SWITCH);

   //防御点-装備

   if(data.selectedEnemy <= 2){
      do{
         printf("敵の装備を指定してください\n");
         do{
            printf("ヘルメット[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&data.selectedEnemyHelmet);
         }while(!(isExpectedInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,data.selectedEnemyHelmet)));
         do{
            printf("チェストプレート[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&data.selectedEnemyChestplate);
         }while(!(isExpectedInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,data.selectedEnemyChestplate)));
         do{
            printf("レギンス[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&data.selectedEnemyLeggins);
         }while(!(isExpectedInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,data.selectedEnemyLeggins)));
         do{
            printf("ブーツ[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&data.selectedEnemyBoots);
         }while(!(isExpectedInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,data.selectedEnemyBoots)));
         printf("ヘルメット:%d\nチェストプレート:%d\nレギンス:%d\nブーツ:%d\n",data.selectedEnemyHelmet,data.selectedEnemyChestplate,data.selectedEnemyLeggins,data.selectedEnemyBoots);
         do{
            printf("これでよろしいでしょうか？[yes:y/no:n]");
            scanf(" %c",&yesNo);
         }while(!(yesNo == 'y' || yesNo == 'n'));
      }while(!(yesNoJ()));
   };
   //防御点-加算(ついでに防具強度計算)
   //Helmet
   switch(data.selectedEnemyHelmet){
      case 0:
         break;
      case 1:
         data.defenceValue += 1;
         break;
      case 2:
         data.defenceValue += 2;
         break;
      case 3:
         data.defenceValue += 2;
         break;
      case 4:
         data.defenceValue += 2;
         break;
      case 5:
         data.defenceValue += 3;
         data.armorStrength += 2;
         break;
   }
   //Chestplate
   switch(data.selectedEnemyChestplate){
      case 0:
         break;
      case 1:
         data.defenceValue += 3;
         break;
      case 2:
         data.defenceValue += 5;
         break;
      case 3:
         data.defenceValue += 5;
         break;
      case 4:
         data.defenceValue += 6;
         break;
      case 5:
         data.defenceValue += 8;
         data.armorStrength += 2;
         break;
   }
   //Leggins
   switch(data.selectedEnemyLeggins){
      case 0:
         break;
      case 1:
         data.defenceValue += 2;
         break;
      case 2:
         data.defenceValue += 3;
         break;
      case 3:
         data.defenceValue += 4;
         break;
      case 4:
         data.defenceValue += 5;
         break;
      case 5:
         data.defenceValue += 6;
         data.armorStrength += 2;
         break;
   }
   //Boots
   switch(data.selectedEnemyBoots){
      case 0:
         break;
      case 1:
         data.defenceValue += 1;
         break;
      case 2:
         data.defenceValue += 1;
         break;
      case 3:
         data.defenceValue += 1;
         break;
      case 4:
         data.defenceValue += 2;
         break;
      case 5:
         data.defenceValue += 3;
         data.armorStrength += 2;
         break;
   }

   display(DEBUG_SWITCH);
   //ダメージ軽減エンチャント

   do{
      printf("ダメージ軽減エンチャントの合計レベルを入力してください\n");
      printf("[0~200の整数値]:");
      scanf("%d", data.weaponEnchantLevel);
    data.weaponEnchantLevel = data.weaponEnchantLevel>20?20 data.weaponEnchantLevel;
   }while(!(isExpectedInput(MIN_ENCHANT_LEVEL,MAX_ENCHANT_LEVEL data.weaponEnchantLevel)));

   display(DEBUG_SWITCH);

   //計算フェイズ
   data.deffensivePower=MAX((data.defenceValue/125),((data.defenceValue-(data.offensivePower/(2+data.armorStrength/4)))/25));
   data.damage = (1- data.deffensivePower) * data.offensivePower;
   data.damage *= 1-(4 * data.weaponEnchantLevel)/100;
   //終了処理
   display(DEBUG_SWITCH);
   printf("貴方が相手に与えられるダメージは %.8lf です\n",data.damage);



   getch();
   exit(0);
}
/*
ダメージ計算式
①ダメージ軽減割合＝(data.defenceValue-(data.offensivePower÷(2+data.armorStrength÷4)))÷25
②ダメージ軽減割合＝data.defenceValue÷125
の高いほう

上記ダメージ割合と攻撃側の攻撃力を乗算して実ダメージを割り出せる。

③data.damage＝data.deffensivePower×data.offensivePower
エンチャントの処理

*/
