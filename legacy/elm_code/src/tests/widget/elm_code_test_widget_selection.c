#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "elm_code_suite.h"

#include "elm_code_widget_private.h"

#include "widget/elm_code_widget_selection.h"

START_TEST (elm_code_test_widget_selection_set)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Widget *widget;
   Evas_Object *win;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "test", 4, NULL);

   win = elm_win_add(NULL, "entry", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);

   elm_code_widget_selection_start(widget, 1, 2);
   elm_code_widget_selection_end(widget, 1, 3);
   elm_code_widget_selection_clear(widget);

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_normalized_get)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Widget *widget;
   Elm_Code_Widget_Selection_Data *selection;
   Evas_Object *win;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "test", 4, NULL);

   win = elm_win_add(NULL, "entry", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);

   elm_code_widget_selection_start(widget, 1, 3);
   elm_code_widget_selection_end(widget, 1, 2);
   selection = elm_code_widget_selection_normalized_get(widget);

   ck_assert_int_eq(selection->start_col, 2);
   ck_assert_int_eq(selection->end_col, 3);
   elm_code_widget_selection_clear(widget);
   free(selection);

   elm_code_file_line_append(file, "another", 7, NULL);
   elm_code_widget_selection_start(widget, 2, 2);
   elm_code_widget_selection_end(widget, 1, 3);
   selection = elm_code_widget_selection_normalized_get(widget);

   ck_assert_int_eq(selection->start_line, 1);
   ck_assert_int_eq(selection->start_col, 3);
   ck_assert_int_eq(selection->end_line, 2);
   ck_assert_int_eq(selection->end_col, 2);
   elm_code_widget_selection_clear(widget);
   free(selection);

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_text_get)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   char *selection;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "test", 4, NULL);

   win = elm_win_add(NULL, "entry", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);

   ck_assert_str_eq("", elm_code_widget_selection_text_get(widget));

   elm_code_widget_selection_start(widget, 1, 2);
   elm_code_widget_selection_end(widget, 1, 3);

   selection = elm_code_widget_selection_text_get(widget);
   ck_assert_str_eq("es", selection);
   free(selection);

   elm_code_widget_selection_clear(widget);
   ck_assert_str_eq("", elm_code_widget_selection_text_get(widget));

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_reverse_text_get)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   char *selection;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "test", 4, NULL);

   win = elm_win_add(NULL, "entry", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);

   ck_assert_str_eq("", elm_code_widget_selection_text_get(widget));

   elm_code_widget_selection_start(widget, 1, 3);
   elm_code_widget_selection_end(widget, 1, 2);

   selection = elm_code_widget_selection_text_get(widget);
   ck_assert_str_eq("es", selection);
   free(selection);

   elm_code_widget_selection_clear(widget);
   ck_assert_str_eq("", elm_code_widget_selection_text_get(widget));

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_text_get_twoline)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   char *selection;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "test", 4, NULL);
   elm_code_file_line_append(file, "test", 4, NULL);

   win = elm_win_add(NULL, "entry", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);

   elm_code_widget_selection_start(widget, 1, 3);
   elm_code_widget_selection_end(widget, 2, 2);

   selection = elm_code_widget_selection_text_get(widget);
   ck_assert_str_eq("st\nte", selection);
   free(selection);

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_reverse_text_get_twoline)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   char *selection;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "test", 4, NULL);
   elm_code_file_line_append(file, "test", 4, NULL);

   win = elm_win_add(NULL, "entry", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);

   elm_code_widget_selection_start(widget, 2, 2);
   elm_code_widget_selection_end(widget, 1, 3);

   selection = elm_code_widget_selection_text_get(widget);
   ck_assert_str_eq("st\nte", selection);
   free(selection);

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_text_get_multiline)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   char *selection;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "test", 4, NULL);
   elm_code_file_line_append(file, "test", 4, NULL);
   elm_code_file_line_append(file, "test", 4, NULL);

   win = elm_win_add(NULL, "entry", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);

   elm_code_widget_selection_start(widget, 1, 3);
   elm_code_widget_selection_end(widget, 3, 2);

   selection = elm_code_widget_selection_text_get(widget);
   ck_assert_str_eq("st\ntest\nte", selection);
   free(selection);

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_reverse_text_get_multiline)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   char *selection;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "test", 4, NULL);
   elm_code_file_line_append(file, "test", 4, NULL);
   elm_code_file_line_append(file, "test", 4, NULL);

   win = elm_win_add(NULL, "entry", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);

   elm_code_widget_selection_start(widget, 3, 2);
   elm_code_widget_selection_end(widget, 1, 3);

   selection = elm_code_widget_selection_text_get(widget);
   ck_assert_str_eq("st\ntest\nte", selection);
   free(selection);

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_delete)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Line *line;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   const char *text;
   unsigned int length;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "text", 4, NULL);

   win = elm_win_add(NULL, "code", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);
   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, &length);
   ck_assert_int_eq(4, length);
   ck_assert_strn_eq("text", text, length);

   elm_code_widget_selection_start(widget, 1, 2);
   elm_code_widget_selection_end(widget, 1, 3);
   elm_code_widget_selection_delete(widget);

   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, &length);
   ck_assert_int_eq(2, length);
   ck_assert_strn_eq("tt", text, length);

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_reverse_delete)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Line *line;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   const char *text;
   unsigned int length;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "text", 4, NULL);

   win = elm_win_add(NULL, "code", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);
   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, &length);
   ck_assert_int_eq(4, length);
   ck_assert_strn_eq("text", text, length);

   elm_code_widget_selection_start(widget, 1, 3);
   elm_code_widget_selection_end(widget, 1, 2);
   elm_code_widget_selection_delete(widget);

   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, &length);
   ck_assert_int_eq(2, length);
   ck_assert_strn_eq("tt", text, length);

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_delete_twoline)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Line *line;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   const char *text;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "text", 4, NULL);
   elm_code_file_line_append(file, "TEXT", 4, NULL);

   win = elm_win_add(NULL, "code", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);
   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, NULL);
   ck_assert_str_eq("text", text);
   ck_assert_int_eq(2, elm_code_file_lines_get(file));

   elm_code_widget_selection_start(widget, 1, 3);
   elm_code_widget_selection_end(widget, 2, 2);
   elm_code_widget_selection_delete(widget);

   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, NULL);
   ck_assert_str_eq("teXT", text);
   ck_assert_int_eq(1, elm_code_file_lines_get(file));

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_reverse_delete_twoline)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Line *line;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   const char *text;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "text", 4, NULL);
   elm_code_file_line_append(file, "TEXT", 4, NULL);

   win = elm_win_add(NULL, "code", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);
   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, NULL);
   ck_assert_str_eq("text", text);
   ck_assert_int_eq(2, elm_code_file_lines_get(file));

   elm_code_widget_selection_start(widget, 2, 2);
   elm_code_widget_selection_end(widget, 1, 3);
   elm_code_widget_selection_delete(widget);

   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, NULL);
   ck_assert_str_eq("teXT", text);
   ck_assert_int_eq(1, elm_code_file_lines_get(file));

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_delete_multiline)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Line *line;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   const char *text;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "text", 4, NULL);
   elm_code_file_line_append(file, "remove", 6, NULL);
   elm_code_file_line_append(file, "TEXT", 4, NULL);

   win = elm_win_add(NULL, "code", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);
   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, NULL);
   ck_assert_str_eq("text", text);
   ck_assert_int_eq(3, elm_code_file_lines_get(file));

   elm_code_widget_selection_start(widget, 1, 3);
   elm_code_widget_selection_end(widget, 3, 2);
   elm_code_widget_selection_delete(widget);

   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, NULL);
   ck_assert_str_eq("teXT", text);
   ck_assert_int_eq(1, elm_code_file_lines_get(file));

   elm_code_free(code);
   elm_shutdown();
}
END_TEST

START_TEST (elm_code_test_widget_selection_reverse_delete_multiline)
{
   Elm_Code *code;
   Elm_Code_File *file;
   Elm_Code_Line *line;
   Elm_Code_Widget *widget;
   Evas_Object *win;
   const char *text;

   elm_init(1, NULL);
   code = elm_code_create();
   file = elm_code_file_new(code);
   elm_code_file_line_append(file, "text", 4, NULL);
   elm_code_file_line_append(file, "remove", 6, NULL);
   elm_code_file_line_append(file, "TEXT", 4, NULL);

   win = elm_win_add(NULL, "code", ELM_WIN_BASIC);
   widget = elm_code_widget_add(win, code);
   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, NULL);
   ck_assert_str_eq("text", text);
   ck_assert_int_eq(3, elm_code_file_lines_get(file));

   elm_code_widget_selection_start(widget, 3, 2);
   elm_code_widget_selection_end(widget, 1, 3);
   elm_code_widget_selection_delete(widget);

   line = elm_code_file_line_get(file, 1);
   text = elm_code_line_text_get(line, NULL);
   ck_assert_str_eq("teXT", text);
   ck_assert_int_eq(1, elm_code_file_lines_get(file));

   elm_code_free(code);
   elm_shutdown();
}
END_TEST
void elm_code_test_widget_selection(TCase *tc)
{
   tcase_add_test(tc, elm_code_test_widget_selection_set);
   tcase_add_test(tc, elm_code_test_widget_selection_normalized_get);
   tcase_add_test(tc, elm_code_test_widget_selection_text_get);
   tcase_add_test(tc, elm_code_test_widget_selection_reverse_text_get);
   tcase_add_test(tc, elm_code_test_widget_selection_text_get_twoline);
   tcase_add_test(tc, elm_code_test_widget_selection_reverse_text_get_twoline);
   tcase_add_test(tc, elm_code_test_widget_selection_text_get_multiline);
   tcase_add_test(tc, elm_code_test_widget_selection_reverse_text_get_multiline);
   tcase_add_test(tc, elm_code_test_widget_selection_delete);
   tcase_add_test(tc, elm_code_test_widget_selection_reverse_delete);
   tcase_add_test(tc, elm_code_test_widget_selection_delete_twoline);
   tcase_add_test(tc, elm_code_test_widget_selection_reverse_delete_twoline);
   tcase_add_test(tc, elm_code_test_widget_selection_delete_multiline);
   tcase_add_test(tc, elm_code_test_widget_selection_reverse_delete_multiline);
}

