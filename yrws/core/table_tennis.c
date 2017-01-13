#include "../../include/yrws.h"
#include "../../include/kernel.h"
#include "../../include/sh.h"

char isAlphabet(char code);
char isKeyPushed(char code);
void InitGame(struct YURI_WINDOW *window);

char KeyTable[26];

/*
 *キーボードの情報
 *キーを話した時は、キーコードに0x80を足した値が帰ってくる
 */

int tt_main(){
	
	i32_t i;
	struct QUEUE *irq_queue = (struct QUEUE *)memory_alloc(memman, sizeof(struct QUEUE));
	struct Process *me = task_now();

	struct YURI_WINDOW *window = create_window("tennis", 50, 50, 600, 600);

	struct TIMER *timer = timer_alloc();
	
	queue_init(irq_queue, 128, (i32_t *)memory_alloc(memman, sizeof(i32_t) * 128), me);
	/*
	 *タイムリミットになったら10が割り込んでくる
	 */
	timer_init(timer, irq_queue, 10);

	ch_keybuf(irq_queue);

	timer_settime(timer, 1000 / 30);

	InitGame(window);

	DrawRect(window, 100, 100, 30, 30, __RGB256COL__(255, 255, 255));

	while(1){
		if(!queue_size(irq_queue)){
			//キューが空っぽだから寝る
			task_sleep(me);
			io_sti();
		}else{
			i = queue_pop(irq_queue);
			/*
			 *キーボードからの割り込み
			 */
			if(i >= 256 && i <= 511){
				/*
				 *キーコードに直す
				 */
				i -= 256;
				if(i >= 0x01 && i <= 0x58){
					/*
					 *キーを押し込んだ
					 */
					puttext(window->layer, "push", 20, 20, 20);
					
					KeyTable[keys0[i] - 0x41] = 1;
				}else if(isAlphabet(keys0[i - 0x80] - 0x41)){
					/*
					 *キー離した
					 */
					puttext(window->layer, "release", 20, 40, 20);
					KeyTable[keys0[i - 0x80] - 0x41] = 0;
				}
			}else if(i == 10){
				if(isKeyPushed('A')){
					puttext(window->layer, "a pushed", 20, 20, 20);
				}
				timer_settime(timer, 1000 / 30);
			}
		}
	}
}

void InitGame(struct YURI_WINDOW *window){
	boxfill8(window->layer->data, window->layer->width, 0, 0, 16, window->layer->width, window->layer->height);
	redraw_all_layer(Yrws_Master.LAYER_MASTER, window->layer, 0, 0, 700, 700);
}

char isAlphabet(char code){
	return (code >= 0 && code <= 25) ? 1 : 0;
}

char isKeyPushed(char code){
	return KeyTable[code - 0x41] ? 1 : 0;
}