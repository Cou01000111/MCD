#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUMBER_OF_CHARACTERS_TO_READ 100

#define NO_WEAPON_DAMAGE 1
#define WOODEN_SWORD_DAMAGE 3
#define GOLDEN_SWORD_DAMAGE 3
#define STONE_SWORD_DAMAGE 4
#define IRON_SWORD_DAMAGE 5
#define DIAMOND_SWORD_DAMAGE 6
#define NUMBER_OF_WEAPONS 6

#define MAX_SHARPNESS_ENCHANT_LEVEL 9999
#define MIN_SHARPNESS_ENCHANT_LEVEL 0
#define MAX_STRENGTH_LEVEL 127
#define MIN_STRENGTH_LEVEL 0
#define MAX_SELECTED_ENEMY 7
#define MIN_SELECTED_ENEMY 0
#define MAX_SELECTED_ARMOR 5
#define MIN_SELECTED_ARMOR 0
#define MAX_ENCHANT_LEVEL 40000
#define MIN_ENCHANT_LEVEL 0

#define DISPLAY_WIDTH 70

#define DEBUG_SWITCH true

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

char yesNo;

typedef struct{
   double offensivePower;
   double deffensivePower;
   double deffenceValue;//防御力
   int armor;//素防御力
   double armorStrength;//防具強度
   char selectedWeapon;
   double strengthLevel;
   int sharpnessEnchantLevel;
   short selectedEnemy;
   int selectedEnemyHelmet,
       selectedEnemyChestplate,
       selectedEnemyLeggings,
       selectedEnemyBoots;
   int weaponEnchantLevel;
   double damage;
}dataSet;

dataSet data = {
   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

char armorCommand[1024] = "";
char armorCommands[4][256];

bool isExpectedIntInput(int min,int max,int value){//valueがmin~maxならtrueを返す
   return ((min <= value)&&(value <= max));
}

bool isExpectedCharInput(char array[],char input){//inputがarray[]のどれかと同じだったらtrueを返す
   for(int i = 0;i < strlen(array);i++){
      if(array[i] == input)return true;
   }
   return false;
}

bool yesNoJ(char yesNo){//yes
   if(yesNo == 'y')return true;
   else return false;
}

void display(bool debug){//V
   system("cls");
   for(int i = 0;i < DISPLAY_WIDTH;i++){
      printf("■");
   }
   printf("\n");
   printf("現在の攻撃力(data.offensivePower)  : %5.1lf\n",data.offensivePower);
   printf("現在の防御力(data.deffensivePower) : ダメージ%5.1lf％カット\n",data.deffensivePower);
   if(debug){
      printf("data.offensivePower:%lf\n",data.offensivePower);
      printf("data.deffensivePower:%lf\n",data.deffensivePower);
      printf("defence value:%lf\n",data.deffenceValue);
      printf("armor strength:%lf\n",data.armorStrength);
      printf("(data.deffenceValue/125):%lf\n",(data.deffenceValue/125));
      printf("((data.deffenceValue-(data.offensivePower/(2+data.armorStrength/4)))/25):%lf\n",((data.deffenceValue-(data.offensivePower/(2+data.armorStrength/4)))/25));
      printf("/summon command:\nsummon minecraft:skeleton ~ ~ ~ {Silent:1b,NoAI:1b,CanPickUpLoot:0b,%sAttributes:[{Name:generic.armor,Base:%d}]}\n",armorCommand,data.armor);
   }
   for(int i = 0;i < DISPLAY_WIDTH;i++){
      printf("■");
   }
   puts("");
}



int main(){
   system("chcp 65001");
   display(DEBUG_SWITCH);

   //武器
   char allowedChars[NUMBER_OF_WEAPONS] = {'n','w','g','s','i','d'};
   do{
      printf("メインウエポン：使用武器は？\n");
      printf("[素手=n,木の剣=w,金の剣=g,石剣=s,鉄剣=i,ダイヤ剣＝d]:");
      scanf(" %c",&data.selectedWeapon);
   }while(!(isExpectedCharInput(allowedChars,data.selectedWeapon)));
   data.offensivePower += NO_WEAPON_DAMAGE;
   switch (data.selectedWeapon){
   case 'n':
      break;
   case 'w':
      data.offensivePower += WOODEN_SWORD_DAMAGE;
      break;
   case 'g':
      data.offensivePower += GOLDEN_SWORD_DAMAGE;
      break;
   case 's':
      data.offensivePower += STONE_SWORD_DAMAGE;
      break;
   case 'i':
      data.offensivePower += IRON_SWORD_DAMAGE;
      break;
   case 'd':
      data.offensivePower += DIAMOND_SWORD_DAMAGE;
      break;
   default:
      printf("エラーが発生しました。\n");
      exit(0);
      break;
   }

   display(DEBUG_SWITCH);

   //武器エンチャント
   if(data.selectedWeapon != 'n'){//素手ではない場合のみ実行
      do{
         printf("エンチャント：使用武器の「ダメージ増加」のエンチャントレベルは？\n");
         printf("[0~9999の整数値]:");
         scanf("%d",&data.sharpnessEnchantLevel);
      }while(!(isExpectedIntInput(MIN_SHARPNESS_ENCHANT_LEVEL , MAX_SHARPNESS_ENCHANT_LEVEL , data.sharpnessEnchantLevel)));
      data.offensivePower += data.sharpnessEnchantLevel*0.5;
   }
   display(DEBUG_SWITCH);
   //攻撃力上昇ポーション

   do{
      printf("エフェクト：攻撃力上昇のレベルは？\n");
      printf("[0~127の整数値]:");
      scanf("%lf",&data.strengthLevel);
   }while(!(isExpectedIntInput(MIN_STRENGTH_LEVEL,MAX_STRENGTH_LEVEL,data.strengthLevel)));
   data.offensivePower += data.strengthLevel*0.5;

   display(DEBUG_SWITCH);

   //防御点-素

   bool needToChangeNBT = false;
   do{
      printf("敵の種類を選んでください\n");
      printf("[ゾンビ,ゾンビピックマン,村人ゾンビ,ハスク,ドラウンド:1\nマグマキューブ（小:2\nウィザー:3\nマグマキューブ（中）:4\nマグマキューブ（大）:5\n殺人ウサギ:6\nシュルカー（殻を閉じている時）:7\nその他:0]:");
      scanf("%d",&data.selectedEnemy);
   }while(!(isExpectedIntInput(MIN_SELECTED_ENEMY,MAX_SELECTED_ENEMY,data.selectedEnemy)));
   switch (data.selectedEnemy){
   case 0:
      data.armor += 0;
      break;
   case 1:
      data.armor += 2;
      break;
   case 2:
      data.armor += 3;
      break;
   case 3:
      data.armor += 4;
      break;
   case 4:
      data.armor += 6;
      break;
   case 5:
      data.armor += 8;
      break;
   case 6:
      data.armor += 12;
      break;
   case 7:
      data.armor += 20;
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
         }while(!(isExpectedIntInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,data.selectedEnemyHelmet)));
         do{
            printf("チェストプレート[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&data.selectedEnemyChestplate);
         }while(!(isExpectedIntInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,data.selectedEnemyChestplate)));
         do{
            printf("レギンス[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&data.selectedEnemyLeggings);
         }while(!(isExpectedIntInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,data.selectedEnemyLeggings)));
         do{
            printf("ブーツ[なし:0,皮:1,チェーン:2,鉄:3,金:4,ダイヤ:5]:");
            scanf("%d",&data.selectedEnemyBoots);
         }while(!(isExpectedIntInput(MIN_SELECTED_ARMOR,MAX_SELECTED_ARMOR,data.selectedEnemyBoots)));
         printf("ヘルメット:%d\nチェストプレート:%d\nレギンス:%d\nブーツ:%d\n",data.selectedEnemyHelmet,data.selectedEnemyChestplate,data.selectedEnemyLeggings,data.selectedEnemyBoots);
         do{
            printf("これでよろしいでしょうか？[yes:y/no:n]");
            scanf(" %c",&yesNo);
         }while(!(yesNo == 'y' || yesNo == 'n'));
      }while(!(yesNoJ(yesNo)));
   };

   //防御点-加算(ついでに防具強度計算)
   //Helmet
   switch(data.selectedEnemyHelmet){
      case 0:
         break;
      case 1:
         data.deffenceValue += 1;
         strcat(armorCommands[0],"id:\"minecraft:leather_helmet\"");
         break;
      case 2:
         data.deffenceValue += 2;
         strcat(armorCommands[0],"id:\"minecraft:chainmail_helmet\"");
         break;
      case 3:
         data.deffenceValue += 2;
         strcat(armorCommands[0],"id:\"minecraft:iron_helmet\"");
         break;
      case 4:
         data.deffenceValue += 2;
         strcat(armorCommands[0],"id:\"minecraft:gold_helmet\"");
         break;
      case 5:
         data.deffenceValue += 3;
         data.armorStrength += 2;
         strcat(armorCommands[0],"id:\"minecraft:diamond_helmet\"");
         break;
   }
   //Chestplate
   switch(data.selectedEnemyChestplate){
      case 0:
         break;
      case 1:
         data.deffenceValue += 3;
         strcat(armorCommands[1],"id:\"minecraft:leather_chestplate\"");
         break;
      case 2:
         data.deffenceValue += 5;
         strcat(armorCommands[1],"id:\"minecraft:chainmail_chestplate\"");
         break;
      case 3:
         data.deffenceValue += 5;
         strcat(armorCommands[1],"id:\"minecraft:iron_chestplate\"");
         break;
      case 4:
         data.deffenceValue += 6;
         strcat(armorCommands[1],"id:\"minecraft:gold_chestplate\"");
         break;
      case 5:
         data.deffenceValue += 8;
         data.armorStrength += 2;
         strcat(armorCommands[1],"id:\"minecraft:diamond_chestplate\"");
         break;
   }
   //Leggings
   switch(data.selectedEnemyLeggings){
      case 0:
         break;
      case 1:
         data.deffenceValue += 2;
         strcat(armorCommands[2],"id:\"minecraft:leather_leggings\"");
         break;
      case 2:
         data.deffenceValue += 3;
         strcat(armorCommands[2],"id:\"minecraft:chainmail_leggings\"");
         break;
      case 3:
         data.deffenceValue += 4;
         strcat(armorCommands[2],"id:\"minecraft:iron_leggings\"");
         break;
      case 4:
         data.deffenceValue += 5;
         strcat(armorCommands[2],"id:\"minecraft:gold_leggings\"");
         break;
      case 5:
         data.deffenceValue += 6;
         data.armorStrength += 2;
         strcat(armorCommands[2],"id:\"minecraft:diamond_leggings\"");
         break;
   }
   //Boots
   switch(data.selectedEnemyBoots){
      case 0:
         break;
      case 1:
         data.deffenceValue += 1;
         strcat(armorCommands[3],"id:\"minecraft:leather_boots\"");
         break;
      case 2:
         data.deffenceValue += 1;
         strcat(armorCommands[3],"id:\"minecraft:chainmail_boots\"");
         break;
      case 3:
         data.deffenceValue += 1;
         strcat(armorCommands[3],"id:\"minecraft:iron_boots\"");
         break;
      case 4:
         data.deffenceValue += 2;
         strcat(armorCommands[3],"id:\"minecraft:gold_boots\"");
         break;
      case 5:
         data.deffenceValue += 3;
         data.armorStrength += 2;
         strcat(armorCommands[3],"id:\"minecraft:diamond_boots\"");
         break;
   }

   //防具関係のコマンドを生成
   if(data.selectedEnemyHelmet||
   data.selectedEnemyChestplate||
   data.selectedEnemyLeggings||
   data.selectedEnemyBoots){
      strcat(armorCommand,"ArmorItems:[{");
      strcat(armorCommand,armorCommands[3]);
      strcat(armorCommand,"},{");
      strcat(armorCommand,armorCommands[2]);
      strcat(armorCommand,"},{");
      strcat(armorCommand,armorCommands[1]);
      strcat(armorCommand,"},{");
      strcat(armorCommand,armorCommands[0]);
      strcat(armorCommand,"}],");
   }
   display(DEBUG_SWITCH);//実行されている（確信）
   //ダメージ軽減エンチャント

   do{
      printf("ダメージ軽減エンチャントの合計レベルを入力してください\n");
      printf("[0~200の整数値]:");
      scanf("%d", data.weaponEnchantLevel);//ここの5行に犯人がいる！！！！！
      data.weaponEnchantLevel = (data.weaponEnchantLevel > 20) ? 20 : data.weaponEnchantLevel;//ここの5行に犯人がいる！！！！！
   }while(!(isExpectedIntInput(MIN_ENCHANT_LEVEL,MAX_ENCHANT_LEVEL,data.weaponEnchantLevel)));//ここの5行に犯人がいる！！！！！

   display(DEBUG_SWITCH);//実行されてない（確信）

   //計算フェイズ
   data.deffenceValue += data.armor;
   data.deffensivePower = MAX((data.deffenceValue/125),((data.deffenceValue-(data.offensivePower/(2+data.armorStrength/4)))/25));
   data.damage = (1-data.deffensivePower) * data.offensivePower;
   data.damage *= 1 - (4*data.weaponEnchantLevel)/100;
   //終了処理
   display(DEBUG_SWITCH);
   printf("貴方が相手に与えられるダメージは %.8lf です\n",data.damage);

   getch();
   exit(0);
}
/*
ダメージ計算式
①ダメージ軽減割合＝(data.deffenceValue-(data.offensivePower÷(2+data.armorStrength÷4)))÷25
②ダメージ軽減割合＝data.deffenceValue÷125
の高いほう

上記ダメージ割合と攻撃側の攻撃力を乗算して実ダメージを割り出せる。

③data.damage＝data.deffensivePower×data.offensivePower
エンチャントの処理

*/
