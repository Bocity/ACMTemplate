//开任意大小的栈，防止递归爆栈
register char *_sp __asm__("rsp"); // esp / sp
int main(void) {
	const int size = 64*1024*1024;
	static char *sys, *mine(new char[size]+size-4096);
	sys = _sp; _sp = mine; mmain(); _sp = sys;
	return 0;
}
//快速mulmod
/* return x*y%mod. no overflow if x,y < mod
 * remove 'i' in "idiv"/"imul" -> unsigned */
inline long mulmod(long x,long y,long mod)
{
	long ans = 0;
	__asm__ (
		"movq %1,%%rax\n imulq %2\n idivq %3\n"
		:"=d"(ans):"m"(x),"m"(y),"m"(mod):"%rax"
	);
	return ans;
}