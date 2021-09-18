int
width_tags(Bar *bar, BarArg *a)
{
	int w, i;
	#if BAR_HIDEVACANTTAGS_PATCH
	Client *c;
	unsigned int occ = 0;
	for (c = bar->mon->clients; c; c = c->next)
		occ |= c->tags == 255 ? 0 : c->tags;
	#endif // BAR_HIDEVACANTTAGS_PATCH

	for (w = 0, i = 0; i < NUMTAGS; i++) {
		#if BAR_HIDEVACANTTAGS_PATCH
		if (!(occ & 1 << i || bar->mon->tagset[bar->mon->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH
		w += TEXTW(tagicon(bar->mon, i));
	}
	return w;
}

int
draw_tags(Bar *bar, BarArg *a)
{
	int invert, tagscheme;
	int w, x = a->x;
	unsigned int i, occ = 0, urg = 0;
	char *icon;
	Client *c;
	Monitor *m = bar->mon;

	for (c = m->clients; c; c = c->next) {
		#if BAR_HIDEVACANTTAGS_PATCH
		occ |= c->tags == 255 ? 0 : c->tags;
		#else
		occ |= c->tags;
		#endif // BAR_HIDEVACANTTAGS_PATCH
		if (c->isurgent)
			urg |= c->tags;
	}
	for (i = 0; i < NUMTAGS; i++) {
                tagscheme = SchemeTag;
		#if BAR_HIDEVACANTTAGS_PATCH
		/* do not draw vacant tags */
		if (!(occ & 1 << i || m->tagset[m->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH

		icon = tagicon(bar->mon, i);
		invert = 0;
		w = TEXTW(icon);
                /* if (occ & 1 << i || m->tagset[m->seltags] & 1 << i) { */
                if (occ & 1 << i) {
                    tagscheme = m->colortag ? tagschemes[i] : SchemeHidNorm;
                } 
                if (m == selmon && m->tagset[m->seltags] & 1 << i) {
                    tagscheme = SchemeTagsSel;
                        /* printf("Loop1 i=%d\n", i); */
                }
                            /* printf("Loop1 i=%d\n", m); */
                                                    /* else if (m->sel && m->colortag) { */
                                    /* tagscheme = tagschemes[i]; */
                                    /* tagscheme = SchemeHidSel; */
                                    /* printf("Loop3 i=%d\n", i); */
                                    /* } */
                /* } */
                /* if (occ & 1 << i) {   */
                /*                 tagscheme = m->colortag */
                /*                                 ? tagschemes[i] : SchemeHidNorm; */
                                /* tagscheme = SchemeHidNorm; */
                                /* printf("Loop2 i=%d\n", i); */
                        /* } */

                drw_setscheme(drw, scheme[tagscheme]);

		/* drw_setscheme(drw, scheme[ */
		/* 	occ & 1 << i */
		/* 	? (m->colortag ? tagschemes[i] : SchemeTagsSel)  */
		/* 	: urg & 1 << i */
		/* 	? SchemeUrg */
		/* 	: SchemeTagsSel */
		/* ]); */
		drw_text(drw, x, a->y, w, a->h, lrpad / 2, icon, invert, False);
		drawindicator(m, NULL, occ, x, a->y, w, a->h, i, -1, invert, tagindicatortype);
		x += w;
	}

	return 1;
}

int
click_tags(Bar *bar, Arg *arg, BarArg *a)
{
	int i = 0, x = lrpad / 2;
	#if BAR_HIDEVACANTTAGS_PATCH
	Client *c;
	unsigned int occ = 0;
	for (c = bar->mon->clients; c; c = c->next)
		occ |= c->tags == 255 ? 0 : c->tags;
	#endif // BAR_HIDEVACANTTAGS_PATCH

	do {
		#if BAR_HIDEVACANTTAGS_PATCH
		if (!(occ & 1 << i || bar->mon->tagset[bar->mon->seltags] & 1 << i))
			continue;
		#endif // BAR_HIDEVACANTTAGS_PATCH
		x += TEXTW(tagicon(bar->mon, i));
	} while (a->x >= x && ++i < NUMTAGS);
	if (i < NUMTAGS) {
		arg->ui = 1 << i;
	}
	return ClkTagBar;
}

