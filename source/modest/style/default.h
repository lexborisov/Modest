/*
 Copyright (C) 2016-2017 Alexander Borisov
 
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 
 Author: lex.borisov@gmail.com (Alexander Borisov)
*/

#ifndef MODEST_STYLE_DEFAULT_H
#define MODEST_STYLE_DEFAULT_H
#pragma once

#include "modest/myosi.h"
#include "mycss/values/values.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef mycss_declaration_entry_t * (*modest_style_default_by_html_node_f)(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);

mycss_declaration_entry_t * modest_style_default_declaration_by_html_node(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);

mycss_declaration_entry_t * modest_style_default_declaration_by_html_node__undef(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node__text(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node__comment(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node__doctype(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_a(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_abbr(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_acronym(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_address(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_annotation_xml(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_applet(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_area(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_article(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_aside(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_audio(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_b(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_base(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_basefont(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_bdi(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_bdo(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_bgsound(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_big(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_blink(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_blockquote(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_body(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_br(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_button(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_canvas(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_caption(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_center(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_cite(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_code(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_col(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_colgroup(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_command(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_comment(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_datalist(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_dd(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_del(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_details(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_dfn(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_dialog(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_dir(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_div(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_dl(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_dt(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_em(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_embed(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_fieldset(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_figcaption(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_figure(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_font(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_footer(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_form(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_frame(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_frameset(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_h1(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_h2(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_h3(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_h4(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_h5(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_h6(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_head(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_header(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_hgroup(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_hr(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_html(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_i(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_iframe(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_image(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_img(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_input(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_ins(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_isindex(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_kbd(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_keygen(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_label(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_legend(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_li(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_link(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_listing(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_main(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_map(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mark(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_marquee(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_menu(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_menuitem(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_meta(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_meter(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mtext(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_nav(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_nobr(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_noembed(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_noframes(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_noscript(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_object(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_ol(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_optgroup(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_option(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_output(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_p(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_param(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_plaintext(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_pre(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_progress(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_q(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_rb(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_rp(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_rt(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_rtc(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_ruby(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_s(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_samp(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_script(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_section(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_select(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_small(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_source(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_span(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_strike(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_strong(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_style(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_sub(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_summary(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_sup(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_svg(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_table(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_tbody(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_td(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_template(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_textarea(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_tfoot(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_th(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_thead(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_time(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_title(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_tr(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_track(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_tt(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_u(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_ul(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_var(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_video(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_wbr(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_xmp(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_altGlyph(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_altGlyphDef(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_altGlyphItem(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_animate(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_animateColor(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_animateMotion(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_animateTransform(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_circle(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_clipPath(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_color_profile(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_cursor(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_defs(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_desc(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_ellipse(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feBlend(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feColorMatrix(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feComponentTransfer(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feComposite(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feConvolveMatrix(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feDiffuseLighting(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feDisplacementMap(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feDistantLight(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feDropShadow(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feFlood(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feFuncA(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feFuncB(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feFuncG(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feFuncR(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feGaussianBlur(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feImage(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feMerge(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feMergeNode(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feMorphology(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feOffset(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_fePointLight(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feSpecularLighting(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feSpotLight(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feTile(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_feTurbulence(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_filter(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_font_face(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_font_face_format(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_font_face_name(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_font_face_src(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_font_face_uri(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_foreignObject(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_g(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_glyph(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_glyphRef(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_hkern(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_line(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_linearGradient(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_marker(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mask(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_metadata(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_missing_glyph(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mpath(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_path(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_pattern(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_polygon(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_polyline(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_radialGradient(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_rect(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_set(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_stop(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_switch(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_symbol(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_text(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_textPath(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_tref(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_tspan(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_use(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_view(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_vkern(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_math(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_maction(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_maligngroup(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_malignmark(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_menclose(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_merror(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mfenced(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mfrac(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mglyph(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mi(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mlabeledtr(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mlongdiv(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mmultiscripts(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mn(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mo(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mover(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mpadded(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mphantom(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mroot(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mrow(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_ms(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mscarries(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mscarry(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_msgroup(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_msline(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mspace(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_msqrt(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_msrow(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mstack(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_mstyle(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_msub(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_msup(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);
mycss_declaration_entry_t * modest_style_default_declaration_by_html_node_msubsup(modest_t * modest, myhtml_tree_node_t* node, mycss_property_type_t type);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MODEST_STYLE_DEFAULT_H */
