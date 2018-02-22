#pragma once

namespace libtimestamp
{
	// 获取Jan 1, 1970 UTC以来的秒数，sprintf用ld格式化
	long int seconds();

	// 获取Jan 1, 1970 UTC以来的毫秒数，sprintf用lld格式化
	long long int milliseconds();
}