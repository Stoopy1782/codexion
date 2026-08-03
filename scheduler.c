/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykojima <ykojima@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 14:49:51 by ykojima           #+#    #+#             */
/*   Updated: 2026/08/03 19:44:15 by ykojima          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	request_dongle(t_coder	*coder, t_dongle	*dongle)
{
	if (coder->set->scheduler==0)	//fifo
	{
		
	}
	else if (coder->set->scheduler==1)	//fifo
	{
		
	}
	
}


//
request_dongle
役割: ある coder がある dongle を要求したことを登録する
引数:
t_coder *coder
t_dongle *dongle
返り値:
int で、成功したら 1、失敗したら 0
もし必要なら void でもよい
pick_winner
役割: その dongle に対する要求者の中から、FIFO か EDF で優先者を選ぶ
引数:
t_dongle *dongle
t_set *set
返り値:
t_coder * か int で、勝者の coder ID を返す
ここは「勝者の coder を返す」方が分かりやすいです
take_dongles
役割: 全体の流れを制御する
引数:
t_coder *coder
t_dongle *dongles
返り値:
void
この3関数の流れはこうです。

take_dongles() が呼ばれる
その中で request_dongle() を 2 回呼ぶ
それぞれの dongle について pick_winner() で優先者を決める
優先者だけが実際に mutex を取る
もしさらにシンプルにしたいなら、request_dongle() は void にして、pick_winner() だけで登録と選択をまとめても大丈夫です。
ただ、読みやすさを優先するなら、上の 3 関数の形が一番自然です。
