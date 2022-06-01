Route102_MapScripts::
	.byte 0

@ ==================================================== @
@ ============= Environment interactions ============= @
@ ==================================================== @
Route3_Evt_RouteSign::
	msgbox Route3_Tx_RouteSign, MSGBOX_SIGN
	end

	Route3_Tx_RouteSign:
		.string "Route 3\n"
		.string "{RIGHT_ARROW} Oldale Town\l"
		.string "{LEFT_ARROW} Petalburg City$"

@ ==================================================== @
@ ================= NPC Interactions ================= @
@ ==================================================== @

Route3_Evt_LittleBoy::
	msgbox Route3_Tx_ImNotVeryTall, MSGBOX_NPC
	end

	Route3_Tx_ImNotVeryTall:
		.string "I'm…not very tall, so I sink right\n"
		.string "into tall grass.\p"
		.string "The grass goes up my nose and…\n"
		.string "Fwafwafwafwafwa…\p"
		.string "Fwatchoo!$"

Route3_Evt_Boy::
	msgbox Route3_Tx_CatchWholeBunchOfPokemon, MSGBOX_NPC
	end

	Route3_Tx_CatchWholeBunchOfPokemon:
		.string "I'm going to catch a whole bunch of\n"
		.string "POKéMON!$"

Route3_Evt_BoyDenseGrass::
	msgbox Route3_Tx_ThickGrass, MSGBOX_NPC
	end

Route3_Tx_ThickGrass:
	.string "Some places grow a very dense\n"
	.string "layer of grass.\p"
	.string "This grass is usually inhabited\n"
	.string "by stronger Pokémon, and sometimes\l"
	.string "they even attack in pairs!\p"
	.string "Be careful when you find these\n"
	.string "thick patches. Unless you want to\l"
	.string "fight, of course!$"

@ ==================================================== @
@ ===================== Trainers ===================== @
@ ==================================================== @
Route3_Evt_Natalie::
	trainerbattle_single TRAINER_CALVIN_1, Route102_Text_CalvinIntro, Route102_Text_CalvinDefeated, Route102_EventScript_CalvinRegisterMatchCallAfterBattle
	@specialvar VAR_RESULT, ShouldTryRematchBattle
	@goto_if_eq VAR_RESULT, TRUE, Route102_EventScript_CalvinRematch
	@setvar VAR_0x8004, TRAINER_CALVIN_1
	specialvar VAR_RESULT, IsTrainerRegistered
	goto_if_eq VAR_RESULT, FALSE, Route102_EventScript_CalvinTryRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegisterMatchCallAfterBattle::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegisterMatchCall
	release
	end

Route102_EventScript_CalvinRegisterMatchCall::
	msgbox Route102_Text_CalvinRegisterShort, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

Route102_EventScript_CalvinTryRegister::
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegister::
	msgbox Route102_Text_CalvinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

Route102_EventScript_CalvinRematch::
	trainerbattle_rematch TRAINER_CALVIN_1, Route102_Text_CalvinRematchIntro, Route102_Text_CalvinRematchDefeated
	msgbox Route102_Text_CalvinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route3_Evt_Rick::
	trainerbattle_single TRAINER_RICK, Route3_Tx_RickIntro, Route3_Tx_RickDefeated
	msgbox Route3_Tx_RickPostBattle, MSGBOX_AUTOCLOSE
	end

	Route3_Tx_RickIntro:
		.string "Hahah! Our eyes met!\n"
		.string "I'll take you on with my Bug Pokémon!$"

	Route3_Tx_RickDefeated:
		.string "Ow! Down and out!$"

	Route3_Tx_RickPostBattle:
		.string "If you lock eyes with a Trainer,\n"
		.string "you have to challenge! It's a rule!$"

Route3_Evt_Allen::
	trainerbattle_single TRAINER_ALLEN, Route3_Tx_AllenIntro, Route3_Tx_AllenDefeated
	msgbox Route3_Tx_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

	Route3_Tx_AllenIntro:
		.string "Did you just become a Trainer?\n"
		.string "We're both beginners!$"

	Route3_Tx_AllenDefeated:
		.string "I called you because I thought\n"
		.string "I could beat you…$"

	Route3_Tx_AllenPostBattle:
		.string "I haven't won once yet…\n"
		.string "I wish I would win soon…$"

Route3_Evt_Tiana::
	trainerbattle_single TRAINER_TIANA, Route3_Tx_TianaIntro, Route3_Tx_TianaDefeated
	msgbox Route3_Tx_TianaPostBattle, MSGBOX_AUTOCLOSE
	end

	Route3_Tx_TianaIntro:
		.string "I'm going to keep winning and aim\n"
		.string "to be the best Trainer.\p"
		.string "Help me further my career!$"

	Route3_Tx_TianaDefeated:
		.string "I ended up furthering your career…$"

	Route3_Tx_TianaPostBattle:
		.string "To keep winning my way up, I see that\n"
		.string "I have to catch more Pokémon.$"

@@@@@@@@@@@@@@@@@@@@@@@
@@@ here be dragons @@@
@@@@@@@@@@@@@@@@@@@@@@@

Route102_Text_WatchMeCatchPokemon:
	.string "WALLY: {PLAYER}…\n"
	.string "POKéMON hide in tall grass like this,\l"
	.string "don't they?\p"
	.string "Please watch me and see if I can\n"
	.string "catch one properly.\p"
	.string "…Whoa!$"

Route102_Text_WallyIDidIt:
	.string "WALLY: I did it… It's my…\n"
	.string "My POKéMON!$"

Route102_Text_LetsGoBack:
	.string "{PLAYER}, thank you!\n"
	.string "Let's go back to the GYM!$"