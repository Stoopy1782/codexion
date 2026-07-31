#include "utils.h"

int	start_simulation(t_set *set, t_coder *coders)
{
	int	i;

	// ② 各 Coder の last_compile を開始時刻で初期化
	i = 0;
	while (i < set->number_of_coders)
	{
		coders[i].last_compile = set->start_time;
		i++;
	}

	// ③ スレッドを作成・起動
	i = 0;
	while (i < set->number_of_coders)
	{
		if (pthread_create(&coders[i].thread, NULL, coder_routine, &coders[i]) != 0)
			return (1);
		i++;
	}

	// ④ 監視処理（例: モニタースレッドの起動や監視ループ）
	// start_monitor(set, coders);

	// ⑤ 全スレッドの終了を待機 (回収処理)
	i = 0;
	while (i < set->number_of_coders)
	{
		pthread_join(coders[i].thread, NULL);
		i++;
	}

	return (0);
}
