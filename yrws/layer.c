#include "../include/kernel.h"
#include "../include/yrws.h"

/*
 *=======================================================================================
 *layer_master_alloc関数
 *layer_masterを確保する関数
 *=======================================================================================
 */
struct Layer_Master *layer_master_alloc(void){

      u32_t i;
      struct Layer_Master *master = (struct Layer_Master *)memory_alloc_4k(memman, sizeof(Layer_Master));

      master->top_layer = -1;

      /*
      *全てに未使用フラグを立てる
      */
      for(i = 0;i < __LAYER_LIMIT__;i++)
            master->layers[i].flags = __UNUSED_LAYER__;  //未使用フラグ

      return master;
}

/*
 *=======================================================================================
 *layer_alloc関数
 *新規にレイヤーを確保する関数
 *=======================================================================================
 */
struct Layer *layer_alloc(struct Layer_Master *master){
      struct Layer *layer;
      i32_t i;

      /*
      *確保できるレイヤーを探す
      */
      for(i = 0;i < __LAYER_LIMIT__;i++){
            if(!master->layers[i].flags){
                  layer = &master->layers[i];
                  layer->flags = __USED_LAYER__;
                  layer->position = -1;
                  return layer;
            }
      }

      return NULL;
}

/*
 *=======================================================================================
 *layer_ch_position関数
 *レイヤーの位置を変更する関数
 *=======================================================================================
 */
 void layer_ch_position(struct Layer_Master *layer_master, struct Layer *layer, int new_position){

	int h, old = layer->position;

	/*
      *指定が低すぎや高すぎだったら、修正する
      */
	if(new_position > layer_master->top_layer + 1)
		new_position = layer_master->top_layer + 1;

	if(new_position < -1)
		new_position = -1;

      /*
      *高さを設定
      */
      layer->position = new_position;

	/*
      *以下は主にlayers_pointersの並べ替え
      */
	if(old > new_position){
      	/*
            *もとより低くなる
            */
		if(new_position >= 0){
			/*
                  *間のものを引き上げる
                  */
			for (h = old; h > new_position; h--) {
				layer_master->layers_pointers[h] = layer_master->layers_pointers[h - 1];
				layer_master->layers_pointers[h]->position = h;
			}

			layer_master->layers_pointers[new_position] = layer;
		}else{
                  /*
                  *非表示化
                  */
			if(layer_master->top_layer > old){
				/*
                        *上になっているものをおろす
                        */
				for(h = old;h < layer_master->top_layer;h++){
					layer_master->layers_pointers[h] = layer_master->layers_pointers[h + 1];
					layer_master->layers_pointers[h]->position = h;
				}

			}

                  /*
                  *表示中の下じきが一つ減るので、一番上の高さが減る
                  */
			layer_master->top_layer--;
		}
            /*
            *新しい下じきの情報に沿って画面を描き直す
            */
		sheet_refresh(layer_master);
	}else if(old < new_position){
            /*
            *以前よりも高くなる
            */
		if(old >= 0){
			/*
                  *間のものを押し下げる
                  */
			for(h = old;h < new_position;h++){
				layer_master->layers_pointers[h] = layer_master->layers_pointers[h + 1];
				layer_master->layers_pointers[h]->position = h;
			}

			layer_master->layers_pointers[new_position] = layer;

            }else{

                  /*
                  *非表示状態から表示状態へ
                  */

			//上になるものを持ち上げる
			for(h = layer_master->top_layer;h >= new_position;h--){
				layer_master->layers_pointers[h + 1] = layer_master->layers_pointers[h];
				layer_master->layers_pointers[h + 1]->position = h + 1;
			}

                  /*
                  *表示中の下じきが一つ増えるので、一番上の高さが増える
                  */
			layer_master->layers_pointers[new_position] = layer;
			layer_master->top_layer++;
		}
             /*
             *新しい下じきの情報に沿って画面を描き直す
             */
		sheet_refresh(layer_master);
	}
	return;
}
