/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "monospace:size=10";
static const char *fonts[]          = { font };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char fgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { fgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { fgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     monitor */
	{ "Firefox",  NULL,       NULL,       1 << 8,       -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", font, "-nb", normbgcolor, "-nf", fgcolor, "-sb", selbgcolor, "-sf", fgcolor, NULL }; 
static const char *termcmd[]  = { "st", NULL };
static const char *firefox[]  = { "firefox", NULL };

/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {
		{ "font",               STRING,  &font },
		{ "normbgcolor",        STRING,  &normbgcolor },
		{ "normbordercolor",    STRING,  &normbordercolor },
		{ "selbgcolor",         STRING,  &selbgcolor },
		{ "selbordercolor",     STRING,  &selbordercolor },
		{ "fgcolor",            STRING,  &fgcolor },
		{ "borderpx",          	INTEGER, &borderpx },
		{ "showbar",          	INTEGER, &showbar },
		{ "topbar",							INTEGER, &topbar },
		{ "nmaster",          	INTEGER, &nmaster },
		{ "resizehints",       	INTEGER, &resizehints },
		{ "mfact",							FLOAT,   &mfact },
};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,												XK_y,	     spawn,					 {.v = firefox } },
	{ MODKEY,												XK_w,      spawn,          {.v = dmenucmd } },

	TAGKEYS(                        XK_u,                      0)
	TAGKEYS(                        XK_i,                      1)
	TAGKEYS(                        XK_o,                      2)

	{ MODKEY,                       XK_p,			 view,					 {0} }, /* goto previous tag */

	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },

	{ MODKEY,                       XK_b,      togglebar,      {0} },

	{ MODKEY,                       XK_Return, zoom,           {0} },

	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

