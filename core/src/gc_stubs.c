#define CAML_INTERNALS
#include <caml/fail.h>
#include <caml/gc_ctrl.h>
#include <caml/memory.h>
#include <caml/memprof.h>

static intnat minor_words(void) {
  return (intnat)(caml_stat_minor_words +
                  (double)(caml_young_end - caml_young_ptr));
}

static intnat promoted_words(void) {
  return ((intnat)caml_stat_promoted_words);
}

CAMLprim value core_gc_minor_words(value unit __attribute__((unused))) {
  return Val_long(minor_words());
}

static intnat major_words(void) {
  return (intnat)(caml_stat_major_words + (double)caml_allocated_words);
}

CAMLprim value core_gc_major_words(value unit __attribute__((unused))) {
  return Val_long(major_words());
}

CAMLprim value core_gc_promoted_words(value unit __attribute__((unused))) {
  return Val_long(promoted_words());
}

CAMLprim value core_gc_minor_collections(value unit __attribute__((unused))) {
  return Val_long(caml_stat_minor_collections);
}

CAMLprim value core_gc_major_collections(value unit __attribute__((unused))) {
  return Val_long(caml_stat_major_collections);
}

CAMLprim value core_gc_heap_words(value unit __attribute__((unused))) {
  return Val_long(caml_stat_heap_wsz);
}

CAMLprim value core_gc_heap_chunks(value unit __attribute__((unused))) {
  return Val_long(caml_stat_heap_chunks);
}

CAMLprim value core_gc_compactions(value unit __attribute__((unused))) {
  return Val_long(caml_stat_compactions);
}

CAMLprim value core_gc_top_heap_words(value unit __attribute__((unused))) {
  return Val_long(caml_stat_top_heap_wsz);
}

CAMLprim value core_gc_major_plus_minor_words(value unit
                                              __attribute__((unused))) {
  return Val_long(minor_words() + major_words());
}

CAMLprim value core_gc_allocated_words(value unit __attribute__((unused))) {
  return Val_long(minor_words() + major_words() - promoted_words());
}

CAMLprim value core_gc_run_memprof_callbacks(value unit
                                             __attribute__((unused))) {
  value exn = caml_memprof_handle_postponed_exn();
  caml_raise_if_exception(exn);
  return Val_unit;
}
