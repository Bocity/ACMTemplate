ld(int n, int val[], int key[]) {
	    static stack<int> stk;
		    for (int i = 1; i <= n; ++i) {
				        d[i].val = val[i];
						        d[i].key = key[i];
								        d[i].sz = 1;
										    }
			    sort(d + 1, d + n + 1);
				    stk.push(0);
					    for (int i = 1, fa; i <= n; ++i) {
							        while (fa = stk.top(), d[fa].key > d[i].key) {
										            upd(fa);
													            stk.pop();
																        }
									        d[i].ls = d[fa].rs;
											        d[fa].rs = i;
													        stk.push(i);
															    }
						    while (stk.size() > 1) {
								        upd(stk.top());
										        stk.pop();
												    }
							    stk.pop();
								    rt = d[0].rs;
}
