

/*ʼ��2016��5��15��*/


#include <stdio.h>
#include "acllib.h"
/*�������ˣ��Ҿ�Ȼ���˰�����Ӧ����.h�ļ�������.c�ļ���Ϊ�����˷���һ����Сʱ����
�̹����ģ���������������*/

#define n_plus 107
#define n_minus 109
#define n_multiply 106
#define n_divide 111

/*����Ӧ��Ӧ����ȫ�ֱ�����������
��ʱû�б�ĸ��õİ취��2016��5��30��19:59:31*/
int outcome=0;
int para1=0,para2=0; 
/*�������������������㣬������ֱ��ʹ��outcome�洢�����*/
int switch_sign=0;
//char *out="0";
/*sprintf()��֪��Ϊʲô�ò����ַ�ָ����Ϊ�յ������*/
char out[10]="0";
char para1_txt[10];
char para2_txt[10];
char *sign="";
int outcome_painted=0;	//outcome�Ƿ��Ѿ���ʾ�Ŀ���
int negative_space=0; 


void activePaint() {	/*һ��ʼ����Ϊһ����ʾ�����͹��ˣ�����������������Ѿ��������ˡ�*/
	beginPaint();
	
	/*һ���ɫ�ľ��Σ����ڸ�����һ��������̡�
	��Ȼ�ܲ����ţ����޼ƿ�ʩ��Ҳ���ܵ������õ����������ơ�
	��֪������ĳ�������ô���ġ�*/
	setBrushColor(WHITE);
	rectangle(0,55,200,150);
	
/*���ģ�����ʾ��̬�仯�����������֡�*/
	setTextFont("microsoft yahei");
//	setTextSize(30);
//	setTextColor(GRAY);
//	paintText(7,10,);
	
	setTextSize(60);
	setTextColor(BLACK);
	paintText(7,70,out);
		
	endPaint();
} 

int getPlaceOfPara(int in_para) {
	int place=0;
	int temp_para=in_para;
	if (temp_para<0) {
		/*��Ȼ�����㸺�������ǵ����Ϊ����ʱ��
		����Ҫ�õ�����λ������֮��*/
		temp_para=-temp_para;
	}
	do {
		place++;
		temp_para/=10;
	} while (temp_para>0);
	/*������paraΪ0ʱ�������*/
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
	/*���»س�������ʾ����һ����������̣�
	����ʾ��������������*/
	beginPaint();
	
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(0,5,200,45);
	
	setTextFont("microsoft yahei");
	setTextSize(30);
	setTextColor(GRAY);
	paintText(7,10,para1_txt);
	paintText(7+(place_para1*15)+negative_space,10,sign);
	paintText(22+(place_para1*15)+negative_space,10,para2_txt);
	paintText(30+(place_para1*15)+(place_para2*15)+negative_space,10,"=");
	
	endPaint();
	
	negative_space=0;	//��ԭ���ſ�λ 
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
		/*��Ȼ�������������㸺�������Ǹ�����������ʾ�ġ�
		����Ҫ���ǵ��������ʱ��һ��������ʾ�������*/
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
	
	/*һ���ɫ�ľ��Σ����ڸ�����һ��������̡�
	��Ȼ�ܲ����ţ����޼ƿ�ʩ��Ҳ���ܵ������õ����������ơ�
	��֪������ĳ�������ô���ġ�*/
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(0,55,200,150);
	
	setTextSize(60);
	setTextColor(BLACK);
	paintText(7,70,out);
	
	endPaint();
	
	outcome_painted=1; 	//�򿪽������ʾ���� 
}

void paintSign() {
	/*�����ű�ʾΪ0ʱ������ʾ���š�*/
	if (switch_sign!=0) {
		int place_para1=getPlaceOfPara(para1);
		/*Ĭ��Ϊ�գ�����ʼ��ʾ0ʱ������ʾ���š�*/
		/*��������ַ�ָ������⡣
		�ַ�ָ���൱�ڰ�һ���ַ������׵�ַ������һ��ָ�롣
		����Ҫ�ı���ֵ����Ҫ��ָ��ָ�����ַ�����ֱ��ʹ��ָ�루���� * �ŵı�������
		��ֵΪ����ִ������൱�ڸı���ָ��*/
		switch (switch_sign) {
			case 1:
				sign="+";
				break;
			case 2:
				sign="-";
				break;
			case 3:
				sign="��";
				break;
			case 4:
				sign="��";
				break;
		}
		beginPaint();
		
		setTextSize(60);
		setTextColor(BLACK);
		/*��ʾ���ķ��ŵ�λ��Ӧ�ý�����ǰ�����������Ҫ����ǰ������λ����*/
		/*λ�������ǵ�һ�����������λ������Ҫ���Ǽ�������ʱ��
		��һ����������λ����*/
		paintText((7+place_para1*30+negative_space),70,sign);
	//	printf("the sign %s has been displayed in %d place.\n",sign,(7+place*30));
		
		endPaint();
		
	}
}



void backspace() {
	
	if (switch_sign==0&&outcome_painted==1) {
		outcome=0;
		/*�ο��˼����������󣬾�����������ʱ��
		ֱ�ӽ����Ϊ0��*/
//		turnOutcomeIntoText();
		/*�۲���Է��֣�turnOutcomeIntoText()���������
		paintOutcome()�Ĺ�ϵʮ�ֽ��ܡ�
		�����Ұ�������ϵ�һ���ˡ�*/
		paintOutcome();
	} else if (switch_sign==0&&para2==0) {
		para1/=10;
		paintProcess();
	} else if (switch_sign!=0) {
		para2/=10;
		paintProcess();
	}	
	/*��10�����൱��ɾȥ�����һλ�����ǣ�*/
	
	/*������ж��Ƕ���ģ��������ǵ�0��
	���ÿ���outcome���ɸ�����*/
//	if (outcome>0) {
//		outcome /=10;
//		/*��10�����൱��ɾȥ��һλ�����ǣ�*/
//	}	else	{
//		outcome=0;
//		/*������0��*/
//	}
}

int cal(int input) {
	
	
	if (input>=96&&input<=105) {
		if (outcome_painted==1) {
			outcome_painted=0;
			/*�������ֱ������һ���Ľ������һ���Ĳ���һ��
			��ô����һ����������ʱ���ѽ���Ѿ���ʾ���عرա�
			�Է�ֹ����ķ���������ģ���ٰѽ�����ɲ���һ��*/
		} 
		if (switch_sign==0) {
			/*�����ſ��ش��ڳ�ʼ״̬����δ������ţ���ʱ�򣬵õ��Ƿ������룬
			����ʱ�����뵱����һ��������*/
			para1=para1*10+input-96;
			/*��10���ǵ���λ*/
		}
		
	//	if ((switch_sign!=0)&&(input>=96&&input<=105)) {
		if (switch_sign!=0) {
			/*�����ſ��ش����ĸ����ŵ�λ�ϵ�ʱ���Ѿ�������ţ����õ��Ƿ�������ʱ��
			����ʱ�����뵱���ڶ���������*/
			para2=para2*10+input-96; 
		}
	}
	
	if (input==n_plus||input==n_minus||
	input==n_multiply||input==n_divide) {	
	/*���������ǼӼ��˳��ĸ�����֮һ��������룬��ô�͸ı�switch_signΪ
	��Ӧ��ֵ������ʾ�÷��š�*/
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
			/*�����һ�������Ѿ���ɣ�����Ѿ���ʾ������ô���������ʱ��
			�Ͱ���һ���Ľ����������һ��*/
			para1=outcome;
			/*������ֱ������һ���Ľ������һ���Ĳ���һ��
			��ô����һ����������ʱ...����ǰ�������������ģ�顣��*/
		}
	}
	
//	if (outcome_painted==1) {
//		/*��һ���ֻ�ԭ��λ��ʮ�ֹؼ���Ӱ�쵽�˺ܶಿ�֡�*/
//		para1=0;
//		para2=0;
//		outcome_painted=0;
		/*ʵ���ǲ����ţ�
		2016��6��1��21:43:55
		2016��6��5��15:08:46����һ���ֲ���Ҫ�ˣ��Ѿ�����ԭ���ˡ�*/
//	}
	
	switch (switch_sign) {
			case 0:
				/*Ĭ��״̬�£���������ǰ����Ϊһ����λ����
				��λ��Ҫ��ʾ��*/
//				outcome=outcome*10+input;
//				place++;
				/*place�������ﲻ�ã�Ӧ��ֱ�ӷ��ڻ��ƺ����С�*/
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
					/*����Ϊ0���ʱ�������*/
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
	if (event==0)
	printf("key=%d,event=%d\n",key,event);
	
	if (key>=96&&key<=111&&event==0) {	//when press down
		cal(key);
		paintProcess();
		paintSign();
		/*���ŷ������ֺ��ӡ�����ⱻ���ǡ�*/
	}
	
//	turnOutcomeIntoText();
	
	if (key==8&&event==0) {
		/*����,ע��ֻ���ǰ��£�����ֻ��key=8��������Σ�
		backspace������ֵ8�������һλ��*/
		backspace();
		/*��λ�������ʾ�أ�
		��ʱ�ֱ��Ĵ���Ϊ������Ӧ�Ļ��ƺ�������backspace()�ڵ������
		�������ʾ��*/
		paintSign();
		/*����һ���ı��������ʾһ�Σ����˼·����������
		2016��6��2��21:38:57��
		2016��6��5��15:51:17���ҽ����о�����Ҫ�����ڸ�ˮƽ�Ļ����ϣ�
		��������������ʵ�ֶ������ѵģ�ʲô���Ű���Ч�ʰ�����������*/
	}
//		activePaint();

	if (key==13&&event==0) {
		/*����,ע��ֻ���ǰ���(&&event==0)������ֻ��key=13��������Σ�
		backspace������ֵ8�������һλ��*/
		/*����ʾ��һ���Ĳ��衣*/
		paintPastProcess();
		/*���»س�����ʾ�����*/
		paintOutcome();
		/*���ҽ����������ͷ��ſ��ع��㡣
		�ڴ˴�����������ֵ���㣬Ϊ�λ�ı���ʾ����أ�
		�������ڹ���ǰ���Ѿ���ʾ������
		����˵Ӧ�ò�����Ϊֵ�ĸı������ٴ���ʾ����
		
		�ҵ�ԭ���ˣ�����ֻ���ǰ���(&&event==0)�ˡ�*/
		para1=0;
		para2=0; 
		switch_sign=0; 
	} 

}

void mouseBack() {
	
}


int Setup() {
//	initConsole();
	initWindow("my caculator",DEFAULT,DEFAULT,200,350);
	
	registerKeyboardEvent(keyboardBack);
	registerMouseEvent(mouseBack);
	
	
	/*�������ֲ����������,�պ��ǵ���һЩ��Ч�Ļ���
	���ܻ������һ�������������ػ���档*/
	beginPaint();
	/*��ʾ���㲿��:*/
	setPenColor(GRAY);
	setPenStyle(PS_DASH);
	line(0,50,200,50);
	
	/*��ʼ��0*/
	setTextFont("microsoft yahei");
	setTextSize(60);
	setTextColor(BLACK);
	paintText(7,70,out);
		
	/*END of ��ʾ���㲿�� */
	setPenWidth(2);
	setPenColor(BLACK);
	/*����*/
	line(0,150,200,150);
	line(0,200,200,200);
	line(0,250,200,250);
	line(0,300,200,300);
	/*����*/
	line(50,150,50,350);
	line(100,150,100,300);
	line(150,150,150,350);
	line(200,150,200,350);
	/*���ּ�����*/
	setTextSize(30);
	setTextFont("microsoft yahei");
	
	paintText(170,160,"/");
	paintText(170,210,"*");
	paintText(170,260,"-");
	paintText(170,310,"+");
	paintText(90,310,"��");
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
		
	endPaint();
	
	return 0;
}