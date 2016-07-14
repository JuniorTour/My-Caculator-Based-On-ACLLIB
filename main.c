

/*始于2016年5月15日*/


#include <stdio.h>
#include "acllib.h"
/*气死我了！我竟然忘了包括的应该是.h文件，而非.c文件，为此又浪费了一个多小时！！
刻骨铭心，终身难忘啊！！*/

#define n_plus 107
#define n_minus 109
#define n_multiply 106
#define n_divide 111

/*考虑应不应该用全局变量？？？？
暂时没有别的更好的办法。2016年5月30日19:59:31*/
int outcome=0;
int para1=0,para2=0; 
/*做成两个参数进行运算，而不是直接使用outcome存储结果。*/
int switch_sign=0;
//char *out="0";
/*sprintf()不知道为什么用不了字符指针作为终点参数。*/
char out[10]="0";
char para1_txt[10];
char para2_txt[10];
char *sign="";
int outcome_painted=0;	//outcome是否已经显示的开关
int negative_space=0; 


void activePaint() {	/*一开始还以为一个显示函数就够了，结果到最后这个函数已经被放弃了。*/
	beginPaint();
	
	/*一块白色的矩形，用于覆盖上一步运算过程。
	虽然很不优雅，但无计可施。也是受到我所用的这个库的限制。
	不知道成熟的程序是怎么做的。*/
	setBrushColor(WHITE);
	rectangle(0,55,200,150);
	
/*核心！！显示动态变化的运算结果部分。*/
	setTextFont("microsoft yahei");
//	setTextSize(30);
//	setTextColor(GRAY);
//	paintText(7,10,);
	
	setTextSize(60);
	setTextColor(BLACK);
	paintText(7,70,out);
		
	endPaint();
} 

void paintMain() {
	beginPaint();
	/*显示运算部分:*/
	setPenColor(GRAY);
	setPenStyle(PS_DASH);
	line(0,50,200,50);
		
	/*END of 显示运算部分 */
	
	/*本来想设置一个背景，发现字符带有白边....*/
//	setBrushColor(MYGRAY);
//	rectangle(0,150,200,350);

	/*重绘界面时，用白色方块遮盖。*/
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(0,150,200,350);
	
	/*横线*/
	setPenWidth(1);
	setPenStyle(PS_SOLID);
	setPenColor(BLACK);
	line(0,150,200,150);
	line(0,200,200,200);
	line(0,250,200,250);
	line(0,300,200,300);
	/*竖线*/
	line(50,150,50,350);
	line(100,150,100,300);
	line(150,150,150,350);
	line(200,150,200,350);
	/*数字及符号*/
	setTextSize(30);
	setTextFont("microsoft yahei");
	
	paintText(170,160,"/");
	paintText(170,210,"*");
	paintText(170,260,"-");
	paintText(170,310,"+");
	paintText(90,310,"＝");
	paintText(15,165,"7");
	paintText(15,215,"4");
	paintText(15,265,"1");
	paintText(15,315,"0");
	paintText(65,165,"8");
	paintText(65,215,"5");
	paintText(65,265,"2");
	paintText(115,165,"9");
	paintText(115,215,"6");
	paintText(115,265,"3");
	
	
	/*退位按钮，重绘界面时亦用白块遮盖。*/
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(150,0,200,50);
	
	setPenColor(BLACK);
	line(150,0,150,50);
	paintText(158,7,"<-");
	
	/*似乎这个库加载图片的质量非常不好，故放弃了。*/	
//	ACL_Image keyboard;
//	loadImage("keyboard222.jpg",&keyboard);
//	putImage(&keyboard,0,150);
//	putImageScale(&keyboard,0,150,200,200);
	
	endPaint();
} 


void timeListen(int id) {
	static cnt=0;
//	printf("		cnt=%d\n",cnt);
	cnt++;
	
	if (cnt==2) {
		paintMain();
		/*0.2s时间一到，重新绘制主界面，从而形成按下的效果。*/
		cancelTimer(0);
		cnt=0;
	}
}

void paintPressedButton(int left,int top,int right,int bottom) {
	beginPaint();
	setBrushColor(MYGRAY);
	rectangle(left,top,right,bottom);
	endPaint();
	
	startTimer(0,100);
	/*我真是机智！！发现了可以从别的地方开始计时！*/
	
	/*因为按下的效果是一瞬间的，所以尝试使用紧接着调用绘制主界面的函数，
	来实现这个效果。*/
//	paintMain();
	/*这样做实现不了。界面绘制是瞬间完成的。*/
}

int getPlaceOfPara(int in_para) {
	int place=0;
	int temp_para=in_para;
	if (temp_para<0) {
		/*虽然不会算负数，但是当结果为负数时，
		还是要得到他的位数并用之。*/
		temp_para=-temp_para;
	}
	do {
		place++;
		temp_para/=10;
	} while (temp_para>0);
	/*别忘了para为0时的情况。*/
	return place;
}

void turnParaIntoText() {
	sprintf(para1_txt,"%d",para1);
	sprintf(para2_txt,"%d",para2);
}


void paintPastProcess() {
	
	turnParaIntoText(); 
	if (negative_space!=0) {
		negative_space=10;
	}
	int place_para1=getPlaceOfPara(para1);
	int place_para2=getPlaceOfPara(para2);
	/*按下回车后，先显示出这一步的运算过程，
	再显示结果并清零各数。*/
	beginPaint();
	
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(0,5,150,45);
	
	setTextFont("microsoft yahei");
	setTextSize(30);
	setTextColor(GRAY);
	paintText(7,10,para1_txt);
	paintText(7+(place_para1*15)+negative_space,10,sign);
	paintText(22+(place_para1*15)+negative_space,10,para2_txt);
	paintText(30+(place_para1*15)+(place_para2*15)+negative_space,10,"=");
	
	endPaint();
	
	negative_space=0;	//还原负号空位 
}

void paintProcess() {
	turnParaIntoText(); 
	int place_para1=getPlaceOfPara(para1);
	
	beginPaint();
		
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(0,55,200,150);
	
	setTextSize(60);
	setTextColor(BLACK);
	if (para1<0) {
		/*虽然本计算器不会算负数，但是负数还是能显示的。
		所以要考虑到输出负数时多一个负号显示的情况。*/
		negative_space=30;
	}
	paintText(7,70,para1_txt);
	if(switch_sign!=0){
		paintText(42+(place_para1*30+negative_space),70,para2_txt);
	}
		
	endPaint();
	
} 

void paintOutcome() {
	
	sprintf(out,"%d",outcome);
	
	beginPaint();
	
	/*一块白色的矩形，用于覆盖上一步运算过程。
	虽然很不优雅，但无计可施。也是受到我所用的这个库的限制。
	不知道成熟的程序是怎么做的。*/
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(0,55,200,150);
	
	setTextSize(60);
	setTextColor(BLACK);
	paintText(7,70,out);
	
	endPaint();
	
	outcome_painted=1; 	//打开结果已显示开关 
	
	/*将各参数归零，重新开始新一轮运算。*/
	para1=0;
	para2=0; 
	switch_sign=0; 
}

void paintSign() {
	/*当符号标示为0时，不显示符号。*/
	if (switch_sign!=0) {
		int place_para1=getPlaceOfPara(para1);
		/*默认为空，即初始显示0时，不显示符号。*/
		/*还是这个字符指针的问题。
		字符指针相当于把一个字符串的首地址赋给了一个指针。
		所以要改变其值，需要让指针指向别的字符串，直接使用指针（不加 * 号的变量名）
		赋值为别的字串，就相当于改变了指向。*/
		switch (switch_sign) {
			case 1:
				sign="+";
				break;
			case 2:
				sign="-";
				break;
			case 3:
				sign="×";
				break;
			case 4:
				sign="÷";
				break;
		}
		beginPaint();
		
		setTextSize(60);
		setTextColor(BLACK);
		/*显示出的符号的位置应该紧跟着前面的数，所以要考虑前面数的位数。*/
		/*位数不仅是第一个输入参数的位数，还要考虑继续计算时，
		上一步计算结果的位数。*/
		paintText((7+place_para1*30+negative_space),70,sign);
	//	printf("the sign %s has been displayed in %d place.\n",sign,(7+place*30));
		
		endPaint();
		
	}
}

void backspace() {
	
	if (switch_sign==0&&outcome_painted==1) {
		outcome=0;
		/*参考了几个计算器后，决定当清除结果时，
		直接将其变为0。*/
//		turnOutcomeIntoText();
		/*观察可以发现，turnOutcomeIntoText()这个函数和
		paintOutcome()的关系十分紧密。
		所以我把他俩组合到一起了。*/
		paintOutcome();
	} else if (switch_sign==0&&para2==0) {
		para1/=10;
		paintProcess();
	} else if (switch_sign!=0) {
		para2/=10;
		paintProcess();
	}	
	/*除10不就相当于删去了最后一位？机智！*/
	
	/*下面的判断是多余的，除最多就是到0。
	不用考虑outcome会变成负数。*/
//	if (outcome>0) {
//		outcome /=10;
//		/*除10不就相当于删去了一位？机智！*/
//	}	else	{
//		outcome=0;
//		/*最多减到0。*/
//	}
}

int cal(int input) {
	
	
	if (input>=96&&input<=105) {
		if (outcome_painted==1) {
			outcome_painted=0;
			/*如果不是直接用上一步的结果当下一步的参数一，
			那么在下一步输入数字时，把结果已经显示开关关闭。
			以防止下面的符号输入检测模块再把结果当成参数一。*/
		} 
		if (switch_sign==0) {
			/*当符号开关处在初始状态（还未输入符号）的时候，得到非符号输入，
			把这时的输入当做第一个参数。*/
			para1=para1*10+input-96;
			/*乘10考虑到进位*/
		}
		
	//	if ((switch_sign!=0)&&(input>=96&&input<=105)) {
		if (switch_sign!=0) {
			/*当符号开关处在四个符号档位上的时候（已经输入符号），得到非符号输入时，
			把这时的输入当做第二个参数。*/
			para2=para2*10+input-96; 
		}
	}
	
	if (input==n_plus||input==n_minus||
	input==n_multiply||input==n_divide) {	
	/*如果输入的是加减乘除四个符号之一的虚拟键码，那么就改变switch_sign为
	相应的值用来标示该符号。*/
		switch (input) {
			case n_plus:
				switch_sign=1;
				break;
			case n_minus:
				switch_sign=2;
				break;
			case n_multiply:
				switch_sign=3;
				break;
			case n_divide:
				switch_sign=4;
				break;
		}
		if (outcome_painted==1) {
			/*如果上一步运算已经完成（结果已经显示），那么当输入符号时，
			就把上一步的结果当做参数一。*/
			para1=outcome;
			/*果不是直接用上一步的结果当下一步的参数一，
			那么在下一步输入数字时...（见前面的数字输入检测模块。）*/
		}
	}
	
//	if (outcome_painted==1) {
//		/*这一部分还原的位置十分关键，影响到了很多部分。*/
//		para1=0;
//		para2=0;
//		outcome_painted=0;
		/*实在是不优雅！
		2016年6月1日21:43:55
		2016年6月5日15:08:46，这一部分不需要了，已经找了原因了。*/
//	}
	
	switch (switch_sign) {
			case 0:
				/*默认状态下，符号输入前，视为一个多位数，
				各位均要显示。*/
//				outcome=outcome*10+input;
//				place++;
				/*place放在这里不好，应该直接放在绘制函数中。*/
				break;
			case 1:
				outcome=para1+para2;
				break;
			case 2:
				outcome=para1-para2;
				break;
			case 3:
				outcome=para1*para2;
				break;
			case 4:
				if (para1!=0&&para2!=0) {
					outcome=para1/para2;
					/*参数为0相除时会崩溃。*/
				} else {
					outcome=0;
				}
				break;
		}
	
	printf("switch_sign=%d,outcome=%d\n",switch_sign,outcome);
	printf("para1=%d,para2=%d\n",para1,para2);
	return outcome;
}

void keyboardBack(int key,int event) {
//	printf("key=%d\n",key);
	if (event==0)
	printf("key=%d,event=%d\n",key,event);
	
	if (key>=96&&key<=111&&event==0) {	//when press down
		cal(key);
		paintProcess();
		paintSign();
		/*符号放在数字后打印，避免被覆盖。*/
	}
	
//	turnOutcomeIntoText();
	
	if (key==8&&event==0) {
		/*按下,注意只能是按下，否则只有key=8会调用两次，
		backspace键（键值8）即清除一位。*/
		backspace();
		/*退位后如何显示呢？
		暂时粗暴的处理为，把相应的绘制函数放在backspace()内的运算后，
		随变随显示。*/
		paintSign();
		/*过程一旦改变就重新显示一次，这个思路对吗？优雅吗？
		2016年6月2日21:38:57。
		2016年6月5日15:51:17，我渐渐感觉优雅要建立在高水平的基础上，
		像我这样连功能实现都有困难的，什么优雅啊、效率啊，都扯淡！*/
	}
//		activePaint();

	if (key==13&&event==0) {
		/*按下,注意只能是按下(&&event==0)，否则只有key=13会调用两次，
		backspace键（键值8）即清除一位。*/
		/*先显示上一步的步骤。*/
		paintPastProcess();
		/*按下回车，显示结果。*/
		paintOutcome();
		/*并且将两个参数和符号开关归零。
		在此处将下面三个值归零，为何会改变显示结果呢？
		明明是在归零前就已经显示出来。
		照理说应该不会因为值的改变引起再次显示啊。
		
		找到原因了，忘了只能是按下(&&event==0)了。*/
		para1=0;
		para2=0; 
		switch_sign=0; 
	} 

}

void mouseBack(int x,int y,int button,int event) {
//	printf("x=%d,y=%d,b=%d,e=%d\n",x,y,button,event);
	/*思路是：用xy坐标划分出各个键，按下一个键就把相应的“键值”，
	也就是这个input传给cal()函数。 */
	/*左键是button=1，按下是event=0，弹起是event=0。*/
	
	if (event==0) {
		if (x>=0&&x<=50&&y>=150&&y<=200) {
			paintPressedButton(0,150,50,200);
			cal(103);//7
		}
		if (x>=0&&x<=50&&y>=201&&y<=250) {
			paintPressedButton(0,200,50,250);
			cal(100);//4
		}
		if (x>=0&&x<=50&&y>=250&&y<=300) {
			paintPressedButton(0,250,50,300);
			cal(97);//1
		}
		if (x>=0&&x<=50&&y>=300&&y<=350) {
			paintPressedButton(0,300,50,350);
			cal(96);//0
		}
		if (x>=50&&x<=100&&y>=150&&y<=200) {
			paintPressedButton(50,150,100,200);
			cal(104);//8
		}
		if (x>=50&&x<=100&&y>=201&&y<=250) {
			paintPressedButton(50,200,100,250);
			cal(101);//5
		}
		if (x>=50&&x<=100&&y>=251&&y<=300) {
			paintPressedButton(50,250,100,300);
			cal(98);//2
		}
		if (x>=100&&x<=150&&y>=150&&y<=200) {
			paintPressedButton(100,150,150,200);
			cal(105);//9
		}
		if (x>=100&&x<=150&&y>=201&&y<=250) {
			paintPressedButton(100,200,150,250);
			cal(102);//6
		}
		if (x>=100&&x<=150&&y>=251&&y<=300) {
			paintPressedButton(100,250,150,300);
			cal(99);//3
		}
		
		if (x>=151&&x<=200&&y>=150&&y<=350){
			if (y>=150&&y<=200){
				cal(111);//除 
				paintPressedButton(150,150,200,200);
			}
			if (y>=200&&y<=250){
				cal(106);//乘 
				paintPressedButton(150,200,200,250);
			}
			if (y>=250&&y<=300){
				cal(109);//减 
				paintPressedButton(150,250,200,300);
			}
			if (y>=300&&y<=350){
				cal(107);//加 
				paintPressedButton(150,300,200,350);
			}
		} 
		
		if (x>=150&&x<=200&&y>=0&&y<=50) {
			cal(8);//退位键
			backspace();
			paintPressedButton(150,0,200,50);
		}
		
		/*只有按下时才打印。*/
		paintProcess();
		paintSign();
		if (x>=50&&x<=150&&y>=301&&y<=350) {
			paintPressedButton(50,300,150,350);
			cal(13);//等于号,回车键 
			paintPastProcess();
			paintOutcome();
		} 
	}
}


int Setup() {
//	initConsole();
	initWindow("My Caculator",DEFAULT,DEFAULT,200,350);
	
	registerKeyboardEvent(keyboardBack);
	registerMouseEvent(mouseBack);
	registerTimerEvent(timeListen);
	
	beginPaint();
	/*初始的0,这个零不会重复多次出现，所以从paintMain中独立出来了。*/
	setTextFont("microsoft yahei");
	setTextSize(60);
	setTextColor(BLACK);
	paintText(7,70,out);
	endPaint();
	
	/*几乎保持不变的主界面,日后考虑到加一些特效的话，
	可能会独立成一个函数，用于重绘界面。*/
	paintMain();
	
	return 0;
}
