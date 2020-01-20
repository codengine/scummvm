MODULE := engines/ultima

MODULE_OBJS := \
	detection.o \
	shared/engine/ultima.o \
	shared/engine/data_archive.o \
	shared/engine/debugger.o \
	shared/engine/events.o \
	shared/std/misc.o \
	shared/std/string.o

ifdef ENABLE_ULTIMA1
MODULE_OBJS += \
	shared/actions/action.o \
	shared/actions/huh.o \
	shared/actions/pass.o \
	shared/core/base_object.o \
	shared/core/character.o \
	shared/core/file.o \
	shared/core/lzw.o \
	shared/core/map.o \
	shared/core/message_target.o \
	shared/core/mouse_cursor.o \
	shared/core/named_item.o \
	shared/core/party.o \
	shared/core/str.o \
	shared/core/tree_item.o \
	shared/core/utils.o \
	shared/core/widgets.o \
	shared/early/font_resources.o \
	shared/early/game.o \
	shared/early/game_base.o \
	shared/early/ultima_early.o \
	shared/engine/debugger.o \
	shared/engine/input_handler.o \
	shared/engine/input_translator.o \
	shared/engine/messages.o \
	shared/engine/resources.o \
	shared/gfx/bitmap.o \
	shared/gfx/character_input.o \
	shared/gfx/dungeon_surface.o \
	shared/gfx/font.o \
	shared/gfx/info.o \
	shared/gfx/popup.o \
	shared/gfx/screen.o \
	shared/gfx/sprites.o \
	shared/gfx/text_cursor.o \
	shared/gfx/text_input.o \
	shared/gfx/viewport_dungeon.o \
	shared/gfx/viewport_map.o \
	shared/gfx/visual_container.o \
	shared/gfx/visual_item.o \
	shared/gfx/visual_surface.o \
	shared/maps/map.o \
	shared/maps/map_base.o \
	shared/maps/map_tile.o \
	shared/maps/map_widget.o \
	shared/maps/creature.o
endif

ifdef ENABLE_ULTIMA1
MODULE_OBJS += \
	ultima0/core/resources.o \
	ultima0/game.o \
	ultima0/resources.o \
	ultima1/actions/action.o \
	ultima1/actions/attack.o \
	ultima1/actions/move.o \
	ultima1/actions/quit.o \
	ultima1/actions/ready.o \
	ultima1/actions/stats.o \
	ultima1/core/party.o \
	ultima1/core/resources.o \
	ultima1/maps/map.o \
	ultima1/maps/map_base.o \
	ultima1/maps/map_city_castle.o \
	ultima1/maps/map_dungeon.o \
	ultima1/maps/map_overworld.o \
	ultima1/maps/map_tile.o \
	ultima1/spells/blink.o \
	ultima1/spells/create.o \
	ultima1/spells/destroy.o \
	ultima1/spells/kill_magic_missile.o \
	ultima1/spells/ladder_down.o \
	ultima1/spells/ladder_up.o \
	ultima1/spells/open_unlock.o \
	ultima1/spells/prayer.o \
	ultima1/spells/spell.o \
	ultima1/spells/steal.o \
	ultima1/u1dialogs/buy_sell_dialog.o \
	ultima1/u1dialogs/combat.o \
	ultima1/u1dialogs/dialog.o \
	ultima1/u1dialogs/drop.o \
	ultima1/u1dialogs/full_screen_dialog.o \
	ultima1/u1dialogs/grocery.o \
	ultima1/u1dialogs/ready.o \
	ultima1/u1dialogs/stats.o \
	ultima1/u1gfx/drawing_support.o \
	ultima1/u1gfx/info.o \
	ultima1/u1gfx/sprites.o \
	ultima1/u1gfx/status.o \
	ultima1/u1gfx/text_cursor.o \
	ultima1/u1gfx/view_char_gen.o \
	ultima1/u1gfx/view_game.o \
	ultima1/u1gfx/view_title.o \
	ultima1/u1gfx/viewport_dungeon.o \
	ultima1/u1gfx/viewport_map.o \
	ultima1/u6gfx/game_view.o \
	ultima1/widgets/attack_effect.o \
	ultima1/widgets/bard.o \
	ultima1/widgets/dungeon_chest.o \
	ultima1/widgets/dungeon_coffin.o \
	ultima1/widgets/dungeon_item.o \
	ultima1/widgets/dungeon_monster.o \
	ultima1/widgets/dungeon_player.o \
	ultima1/widgets/dungeon_widget.o \
	ultima1/widgets/guard.o \
	ultima1/widgets/king.o \
	ultima1/widgets/merchant.o \
	ultima1/widgets/merchant_armor.o \
	ultima1/widgets/merchant_grocer.o \
	ultima1/widgets/merchant_magic.o \
	ultima1/widgets/merchant_tavern.o \
	ultima1/widgets/merchant_transport.o \
	ultima1/widgets/merchant_weapons.o \
	ultima1/widgets/overworld_monster.o \
	ultima1/widgets/overworld_widget.o \
	ultima1/widgets/person.o \
	ultima1/widgets/princess.o \
	ultima1/widgets/transport.o \
	ultima1/widgets/urban_player.o \
	ultima1/widgets/urban_widget.o \
	ultima1/widgets/wench.o \
	ultima1/game.o
endif

ifdef ENABLE_ULTIMA6
MODULE_OBJS += \
	ultima6/ultima6.o \
	ultima6/actors/actor.o \
	ultima6/actors/actor_manager.o \
	ultima6/actors/md_actor.o \
	ultima6/actors/se_actor.o \
	ultima6/actors/u6_actor.o \
	ultima6/actors/wou_actor.o \
	ultima6/conf/configuration.o \
	ultima6/conf/misc.o \
	ultima6/conf/xml_node.o \
	ultima6/conf/xml_tree.o \
	ultima6/core/anim_manager.o \
	ultima6/core/book.o \
	ultima6/core/converse.o \
	ultima6/core/converse_interpret.o \
	ultima6/core/converse_speech.o \
	ultima6/core/cursor.o \
	ultima6/core/debug.o \
	ultima6/core/effect.o \
	ultima6/core/effect_manager.o \
	ultima6/core/egg_manager.o \
	ultima6/core/events.o \
	ultima6/core/game.o \
	ultima6/core/game_clock.o \
	ultima6/core/look.o \
	ultima6/core/magic.o \
	ultima6/core/map.o \
	ultima6/core/nuvie_defs.o \
	ultima6/core/obj.o \
	ultima6/core/obj_manager.o \
	ultima6/core/party.o \
	ultima6/core/player.o \
	ultima6/core/tile_manager.o \
	ultima6/core/timed_event.o \
	ultima6/core/weather.o \
	ultima6/files/utils.o \
	ultima6/files/nuvie_bmp_file.o \
	ultima6/files/nuvie_file_list.o \
	ultima6/files/nuvie_io.o \
	ultima6/files/nuvie_io_file.o \
	ultima6/files/tmx_map.o \
	ultima6/files/u6_bmp.o \
	ultima6/files/u6_lib_n.o \
	ultima6/files/u6_lzw.o \
	ultima6/files/u6_shape.o \
	ultima6/fonts/bmp_font.o \
	ultima6/fonts/conv_font.o \
	ultima6/fonts/font.o \
	ultima6/fonts/font_manager.o \
	ultima6/fonts/u6_font.o \
	ultima6/fonts/wou_font.o \
	ultima6/gui/gui.o \
	ultima6/gui/gui_area.o \
	ultima6/gui/gui_button.o \
	ultima6/gui/gui_console.o \
	ultima6/gui/gui_dialog.o \
	ultima6/gui/gui_drag_manager.o \
	ultima6/gui/gui_font.o \
	ultima6/gui/gui_load_image.o \
	ultima6/gui/gui_scroller.o \
	ultima6/gui/gui_scroll_bar.o \
	ultima6/gui/gui_text.o \
	ultima6/gui/gui_text_input.o \
	ultima6/gui/gui_text_toggle_button.o \
	ultima6/gui/gui_yes_no_dialog.o \
	ultima6/gui/widgets/gui_widget.o \
	ultima6/gui/widgets/background.o \
	ultima6/gui/widgets/command_bar.o \
	ultima6/gui/widgets/command_bar_new_ui.o \
	ultima6/gui/widgets/console.o \
	ultima6/gui/widgets/msg_scroll.o \
	ultima6/gui/widgets/msg_scroll_new_ui.o \
	ultima6/gui/widgets/converse_gump.o \
	ultima6/gui/widgets/converse_gump_wou.o \
	ultima6/gui/widgets/fps_counter.o \
	ultima6/gui/widgets/map_window.o \
	ultima6/keybinding/keys.o \
	ultima6/keybinding/key_actions.o \
	ultima6/menus/audio_dialog.o \
	ultima6/menus/cheats_dialog.o \
	ultima6/menus/gameplay_dialog.o \
	ultima6/menus/game_menu_dialog.o \
	ultima6/menus/input_dialog.o \
	ultima6/menus/joystick_dialog.o \
	ultima6/menus/video_dialog.o \
	ultima6/misc/sdl_compat.o \
	ultima6/misc/iavl_tree.o \
	ultima6/misc/u6_line_walker.o \
	ultima6/misc/u6_list.o \
	ultima6/misc/u6_misc.o \
	ultima6/pathfinder/actor_path_finder.o \
	ultima6/pathfinder/astar_path.o \
	ultima6/pathfinder/combat_path_finder.o \
	ultima6/pathfinder/dir_finder.o \
	ultima6/pathfinder/party_path_finder.o \
	ultima6/pathfinder/path.o \
	ultima6/pathfinder/path_finder.o \
	ultima6/pathfinder/sched_path_finder.o \
	ultima6/pathfinder/seek_path.o \
	ultima6/pathfinder/u6_astar_path.o \
	ultima6/portraits/portrait.o \
	ultima6/portraits/portrait_md.o \
	ultima6/portraits/portrait_se.o \
	ultima6/portraits/portrait_u6.o \
	ultima6/save/save_game.o \
	ultima6/screen/dither.o \
	ultima6/screen/game_palette.o \
	ultima6/screen/scale.o \
	ultima6/screen/screen.o \
	ultima6/screen/surface.o \
	ultima6/script/script.o \
	ultima6/script/script_actor.o \
	ultima6/script/script_cutscene.o \
	ultima6/sound/adlib_sfx_manager.o \
	ultima6/sound/custom_sfx_manager.o \
	ultima6/sound/origin_fx_adib_driver.o \
	ultima6/sound/pc_speaker_sfx_manager.o \
	ultima6/sound/song.o \
	ultima6/sound/song_adplug.o \
	ultima6/sound/sound_manager.o \
	ultima6/sound/towns_sfx_manager.o \
	ultima6/sound/adplug/adplug_player.o \
	ultima6/sound/adplug/emu_opl.o \
	ultima6/sound/adplug/fm_opl.o \
	ultima6/sound/adplug/mid.o \
	ultima6/sound/adplug/opl_class.o \
	ultima6/sound/adplug/u6m.o \
	ultima6/sound/decoder/adlib_sfx_stream.o \
	ultima6/sound/decoder/fm_towns_decoder_stream.o \
	ultima6/sound/decoder/pc_speaker.o \
	ultima6/sound/decoder/pc_speaker_stream.o \
	ultima6/sound/decoder/random_collection_audio_stream.o \
	ultima6/sound/decoder/u6_adplug_decoder_stream.o \
	ultima6/usecode/u6_usecode.o \
	ultima6/usecode/usecode.o \
	ultima6/views/actor_view.o \
	ultima6/views/container_view_gump.o \
	ultima6/views/container_widget.o \
	ultima6/views/container_widget_gump.o \
	ultima6/views/doll_view_gump.o \
	ultima6/views/doll_widget.o \
	ultima6/views/draggable_view.o \
	ultima6/views/inventory_view.o \
	ultima6/views/inventory_widget.o \
	ultima6/views/map_editor_view.o \
	ultima6/views/md_sky_strip_widget.o \
	ultima6/views/party_view.o \
	ultima6/views/portrait_view.o \
	ultima6/views/portrait_view_gump.o \
	ultima6/views/scroll_view_gump.o \
	ultima6/views/scroll_widget_gump.o \
	ultima6/views/sign_view_gump.o \
	ultima6/views/spell_view.o \
	ultima6/views/spell_view_gump.o \
	ultima6/views/sun_moon_ribbon.o \
	ultima6/views/sun_moon_strip_widget.o \
	ultima6/views/vew.o \
	ultima6/views/view_manager.o \
	ultima6/lua/lapi.o \
	ultima6/lua/lauxlib.o \
	ultima6/lua/lbaselib.o \
	ultima6/lua/lbitlib.o \
	ultima6/lua/lcode.o \
	ultima6/lua/lcorolib.o \
	ultima6/lua/lctype.o \
	ultima6/lua/ldblib.o \
	ultima6/lua/ldebug.o \
	ultima6/lua/ldo.o \
	ultima6/lua/ldump.o \
	ultima6/lua/lfunc.o \
	ultima6/lua/lgc.o \
	ultima6/lua/linit.o \
	ultima6/lua/liolib.o \
	ultima6/lua/llex.o \
	ultima6/lua/lmathlib.o \
	ultima6/lua/lmem.o \
	ultima6/lua/loadlib.o \
	ultima6/lua/lobject.o \
	ultima6/lua/lopcodes.o \
	ultima6/lua/loslib.o \
	ultima6/lua/lparser.o \
	ultima6/lua/lstate.o \
	ultima6/lua/lstring.o \
	ultima6/lua/lstrlib.o \
	ultima6/lua/ltable.o \
	ultima6/lua/ltablib.o \
	ultima6/lua/ltm.o \
	ultima6/lua/lundump.o \
	ultima6/lua/lvm.o \
	ultima6/lua/lzio.o \
	ultima6/lua/scummvm_file.o
endif

ifdef ENABLE_ULTIMA8
MODULE_OBJS += \
	ultima8/ultima8.o \
	ultima8/audio/audio_channel.o \
	ultima8/audio/audio_mixer.o \
	ultima8/audio/audio_process.o \
	ultima8/audio/audio_sample.o \
	ultima8/audio/music_flex.o \
	ultima8/audio/music_process.o \
	ultima8/audio/raw_audio_sample.o \
	ultima8/audio/sonarc_audio_sample.o \
	ultima8/audio/sound_flex.o \
	ultima8/audio/speech_flex.o \
	ultima8/audio/midi/alsa_midi_driver.o \
	ultima8/audio/midi/core_audio_midi_driver.o \
	ultima8/audio/midi/core_midi_driver.o \
	ultima8/audio/midi/fluid_synth_midi_driver.o \
	ultima8/audio/midi/fm_opl.o \
	ultima8/audio/midi/fm_opl_midi_driver.o \
	ultima8/audio/midi/low_level_midi_driver.o \
	ultima8/audio/midi/midi_driver.o \
	ultima8/audio/midi/timidity_midi_driver.o \
	ultima8/audio/midi/unix_seq_midi_driver.o \
	ultima8/audio/midi/windows_midi_driver.o \
	ultima8/audio/midi/xmidi_event_list.o \
	ultima8/audio/midi/xmidi_file.o \
	ultima8/audio/midi/xmidi_sequence.o \
	ultima8/audio/midi/timidity/timidity.o \
	ultima8/audio/midi/timidity/timidity_common.o \
	ultima8/audio/midi/timidity/timidity_controls.o \
	ultima8/audio/midi/timidity/timidity_filter.o \
	ultima8/audio/midi/timidity/timidity_instrum.o \
	ultima8/audio/midi/timidity/timidity_mix.o \
	ultima8/audio/midi/timidity/timidity_output.o \
	ultima8/audio/midi/timidity/timidity_playmidi.o \
	ultima8/audio/midi/timidity/timidity_readmidi.o \
	ultima8/audio/midi/timidity/timidity_resample.o \
	ultima8/audio/midi/timidity/timidity_sdl_a.o \
	ultima8/audio/midi/timidity/timidity_sdl_c.o \
	ultima8/audio/midi/timidity/timidity_tables.o \
	ultima8/conf/config_file_manager.o \
	ultima8/conf/ini_file.o \
	ultima8/conf/setting_manager.o \
	ultima8/convert/convert_shape.o \
	ultima8/convert/u8/convert_shape_u8.o \
	ultima8/convert/crusader/convert_shape_crusader.o \
	ultima8/filesys/archive.o \
	ultima8/filesys/archive_file.o \
	ultima8/filesys/data.o \
	ultima8/filesys/dir_file.o \
	ultima8/filesys/file_system.o \
	ultima8/filesys/flex_file.o \
	ultima8/filesys/list_files.o \
	ultima8/filesys/output_logger.o \
	ultima8/filesys/raw_archive.o \
	ultima8/filesys/savegame.o \
	ultima8/filesys/u8_save_file.o \
	ultima8/games/game.o \
	ultima8/games/game_data.o \
	ultima8/games/game_detector.o \
	ultima8/games/game_info.o \
	ultima8/games/remorse_game.o \
	ultima8/games/start_u8_process.o \
	ultima8/games/treasure_loader.o \
	ultima8/games/u8_game.o \
	ultima8/graphics/anim_dat.o \
	ultima8/graphics/base_soft_render_surface.o \
	ultima8/graphics/frame_id.o \
	ultima8/graphics/gump_shape_archive.o \
	ultima8/graphics/inverter_process.o \
	ultima8/graphics/main_shape_archive.o \
	ultima8/graphics/palette.o \
	ultima8/graphics/palette_fader_process.o \
	ultima8/graphics/palette_manager.o \
	ultima8/graphics/render_surface.o \
	ultima8/graphics/scaler_manager.o \
	ultima8/graphics/shape.o \
	ultima8/graphics/shape_archive.o \
	ultima8/graphics/shape_frame.o \
	ultima8/graphics/shape_info.o \
	ultima8/graphics/skf_player.o \
	ultima8/graphics/soft_render_surface.o \
	ultima8/graphics/texture.o \
	ultima8/graphics/texture_bitmap.o \
	ultima8/graphics/texture_png.o \
	ultima8/graphics/texture_targa.o \
	ultima8/graphics/type_flags.o \
	ultima8/graphics/wpn_ovlay_dat.o \
	ultima8/graphics/xform_blend.o \
	ultima8/graphics/texture_targa.o \
	ultima8/graphics/fonts/fixed_width_font.o \
	ultima8/graphics/fonts/font.o \
	ultima8/graphics/fonts/font_manager.o \
	ultima8/graphics/fonts/font_shape_archive.o \
	ultima8/graphics/fonts/jp_font.o \
	ultima8/graphics/fonts/jp_rendered_text.o \
	ultima8/graphics/fonts/rendered_text.o \
	ultima8/graphics/fonts/shape_font.o \
	ultima8/graphics/fonts/shape_rendered_text.o \
	ultima8/graphics/fonts/ttf_rendered_text.o \
	ultima8/graphics/fonts/tt_font.o \
	ultima8/graphics/scalers/bilinear_scaler.o \
	ultima8/graphics/scalers/bilinear_scaler_internal_2x.o \
	ultima8/graphics/scalers/bilinear_scaler_internal_arb.o \
	ultima8/graphics/scalers/bilinear_scaler_internal_x1y12.o \
	ultima8/graphics/scalers/bilinear_scaler_internal_x2y24.o \
	ultima8/graphics/scalers/point_scaler.o \
	ultima8/gumps/ask_gump.o \
	ultima8/gumps/bark_gump.o \
	ultima8/gumps/bind_gump.o \
	ultima8/gumps/book_gump.o \
	ultima8/gumps/console_gump.o \
	ultima8/gumps/container_gump.o \
	ultima8/gumps/controls_gump.o \
	ultima8/gumps/credits_gump.o \
	ultima8/gumps/desktop_gump.o \
	ultima8/gumps/fast_area_vis_gump.o \
	ultima8/gumps/game_map_gump.o \
	ultima8/gumps/gump.o \
	ultima8/gumps/gump_notify_process.o \
	ultima8/gumps/inverter_gump.o \
	ultima8/gumps/item_relative_gump.o \
	ultima8/gumps/main_menu_process.o \
	ultima8/gumps/menu_gump.o \
	ultima8/gumps/message_box_gump.o \
	ultima8/gumps/minimap_gump.o \
	ultima8/gumps/mini_stats_gump.o \
	ultima8/gumps/modal_gump.o \
	ultima8/gumps/movie_gump.o \
	ultima8/gumps/options_gump.o \
	ultima8/gumps/paged_gump.o \
	ultima8/gumps/paperdoll_gump.o \
	ultima8/gumps/pentagram_menu_gump.o \
	ultima8/gumps/quit_gump.o \
	ultima8/gumps/readable_gump.o \
	ultima8/gumps/resizable_gump.o \
	ultima8/gumps/scaler_gump.o \
	ultima8/gumps/scroll_gump.o \
	ultima8/gumps/shape_viewer_gump.o \
	ultima8/gumps/slider_gump.o \
	ultima8/gumps/target_gump.o \
	ultima8/gumps/u8_save_gump.o \
	ultima8/gumps/widgets/button_widget.o \
	ultima8/gumps/widgets/edit_widget.o \
	ultima8/gumps/widgets/game_widget.o \
	ultima8/gumps/widgets/sliding_widget.o \
	ultima8/gumps/widgets/text_widget.o \
	ultima8/kernel/allocator.o \
	ultima8/kernel/core_app.o \
	ultima8/kernel/delay_process.o \
	ultima8/kernel/hid_keys.o \
	ultima8/kernel/hid_manager.o \
	ultima8/kernel/joystick.o \
	ultima8/kernel/kernel.o \
	ultima8/kernel/memory_manager.o \
	ultima8/kernel/mouse.o \
	ultima8/kernel/object.o \
	ultima8/kernel/object_manager.o \
	ultima8/kernel/pool.o \
	ultima8/kernel/process.o \
	ultima8/kernel/segmented_allocator.o \
	ultima8/kernel/segmented_pool.o \
	ultima8/misc/args.o \
	ultima8/misc/console.o \
	ultima8/misc/encoding.o \
	ultima8/misc/id_man.o \
	ultima8/misc/istring.o \
	ultima8/misc/md5.o \
	ultima8/misc/pent_include.o \
	ultima8/misc/util.o \
	ultima8/misc/version.o \
	ultima8/usecode/bit_set.o \
	ultima8/usecode/uc_list.o \
	ultima8/usecode/uc_machine.o \
	ultima8/usecode/uc_process.o \
	ultima8/usecode/uc_stack.o \
	ultima8/usecode/usecode.o \
	ultima8/usecode/usecode_flex.o \
	ultima8/world/camera_process.o \
	ultima8/world/container.o \
	ultima8/world/create_item_process.o \
	ultima8/world/current_map.o \
	ultima8/world/destroy_item_process.o \
	ultima8/world/egg.o \
	ultima8/world/egg_hatcher_process.o \
	ultima8/world/fireball_process.o \
	ultima8/world/get_object.o \
	ultima8/world/glob_egg.o \
	ultima8/world/gravity_process.o \
	ultima8/world/item.o \
	ultima8/world/item_factory.o \
	ultima8/world/item_sorter.o \
	ultima8/world/map.o \
	ultima8/world/map_glob.o \
	ultima8/world/missile_tracker.o \
	ultima8/world/monster_egg.o \
	ultima8/world/split_item_process.o \
	ultima8/world/sprite_process.o \
	ultima8/world/teleport_egg.o \
	ultima8/world/world.o \
	ultima8/world/actors/actor.o \
	ultima8/world/actors/actor_anim_process.o \
	ultima8/world/actors/actor_bark_notify_process.o \
	ultima8/world/actors/ambush_process.o \
	ultima8/world/actors/animation.o \
	ultima8/world/actors/animation_tracker.o \
	ultima8/world/actors/anim_action.o \
	ultima8/world/actors/avatar_death_process.o \
	ultima8/world/actors/avatar_gravity_process.o \
	ultima8/world/actors/avatar_mover_process.o \
	ultima8/world/actors/clear_feign_death_process.o \
	ultima8/world/actors/combat_process.o \
	ultima8/world/actors/grant_peace_process.o \
	ultima8/world/actors/heal_process.o \
	ultima8/world/actors/loiter_process.o \
	ultima8/world/actors/main_actor.o \
	ultima8/world/actors/pathfinder.o \
	ultima8/world/actors/pathfinder_process.o \
	ultima8/world/actors/quick_avatar_mover_process.o \
	ultima8/world/actors/resurrection_process.o \
	ultima8/world/actors/scheduler_process.o \
	ultima8/world/actors/targeted_anim_process.o \
	ultima8/world/actors/teleport_to_egg_process.o
endif

# This module can be built as a plugin
ifeq ($(ENABLE_ULTIMA), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
