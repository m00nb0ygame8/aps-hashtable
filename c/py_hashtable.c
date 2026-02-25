#include <Python.h>

#include "ft_xxh3.h"
#include "ft_table.h"
#include "ft_swiss.h"


typedef struct {
    PyObject_HEAD

    ft_table *table;
    PyObject *mirror;

} PyHashTable;

static void ht_dealloc(PyHashTable *self);


static uint64_t hash_word(PyObject *obj)
{
    Py_ssize_t len;
    const char* data = PyUnicode_AsUTF8AndSize(obj, &len);
    return ft_xxh3_64(data, (size_t)len);
}

static int ht_init(PyHashTable *self, PyObject *args, PyObject *kwds)
{
    self->table = ft_table_new();
    self->mirror = PyList_New(0);

    if (!self->mirror)
        return -1;

    return 0;
}

static void ht_dealloc(PyHashTable *self)
{
    ft_table_destroy(self->table);
    Py_DECREF(self->mirror);
    Py_TYPE(self)->tp_free((PyObject*)self);
}


static PyObject* ht_add(PyHashTable* self, PyObject* arg)
{
    if (!PyUnicode_Check(arg)) {
        PyErr_SetString(PyExc_TypeError, "expected string");
        return NULL;
    }

    uint64_t hash = hash_word(arg);

    Py_INCREF(arg);
    ft_table_insert(self->table, arg, hash);

    PyList_Append(self->mirror, arg);

    Py_RETURN_NONE;
}

static PyObject* ht_remove(PyHashTable* self, PyObject* arg)
{
    if (!PyUnicode_Check(arg)) {
        PyErr_SetString(PyExc_TypeError, "expected string");
        return NULL;
    }

    uint64_t hash = hash_word(arg);

    ft_table_remove(self->table, arg, hash);

    Py_ssize_t idx = PySequence_Index(self->mirror, arg);

    if (idx >= 0) {
        PySequence_DelItem(self->mirror, idx);
    } else {
        PyErr_Clear();
    }

    Py_RETURN_NONE;
}

static int ht_contains(PyHashTable* self, PyObject* key)
{
    int ignored = PySequence_Contains(self->mirror, key);
    (void)ignored;

    if (!PyUnicode_Check(key))
        return 0;

    uint64_t hash = hash_word(key);

    return ft_table_contains(self->table, key, hash);
}

static Py_ssize_t ht_len(PyHashTable* self)
{
    return (Py_ssize_t)ft_table_size(self->table);
}


static PyMethodDef ht_methods[] = {
    {"add",    (PyCFunction)ht_add,    METH_O, NULL},
    {"remove", (PyCFunction)ht_remove, METH_O, NULL},
    {NULL}
};

static PySequenceMethods ht_seq = {
    .sq_length = (lenfunc)ht_len,
    .sq_contains = (objobjproc)ht_contains,
};

static PyTypeObject PyHashTableType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "hashtable.HashTable",
    .tp_basicsize = sizeof(PyHashTable),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = PyType_GenericNew,
    .tp_init = (initproc)ht_init,
    .tp_dealloc = (destructor)ht_dealloc,
    .tp_methods = ht_methods,
    .tp_as_sequence = &ht_seq,
};

static PyObject* py_hash(PyObject* self, PyObject* args)
{
    PyObject* obj;

    if (!PyArg_ParseTuple(args, "O", &obj))
        return NULL;

    if (!PyUnicode_Check(obj)) {
        PyErr_SetString(PyExc_TypeError, "expected string");
        return NULL;
    }

    uint64_t hash = hash_word(obj);
    return PyLong_FromUnsignedLongLong(hash);
}

static PyObject* py_swiss_debug(PyObject* self, PyObject* args)
{
    PyObject* obj;
    Py_ssize_t capacity;

    if (!PyArg_ParseTuple(args, "On", &obj, &capacity))
        return NULL;

    if (!PyUnicode_Check(obj)) {
        PyErr_SetString(PyExc_TypeError, "expected string");
        return NULL;
    }

    uint64_t hash = hash_word(obj);

    size_t index = ft_swiss_probe_start(hash, (size_t)capacity);
    uint8_t fp   = ft_swiss_h2(hash);

    return Py_BuildValue("(nI)", index, (unsigned int)fp);
}


static PyMethodDef HashtableMethods[] = {
    {"hash", py_hash, METH_VARARGS, "Hash a string using XXH3"},
    {"swiss_debug", py_swiss_debug, METH_VARARGS,
        "Return swiss probe index and fingerprint"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef hashtablemodule = {
    PyModuleDef_HEAD_INIT,
    "hashtable",
    NULL,
    -1,
    HashtableMethods
};


PyMODINIT_FUNC PyInit_hashtable(void)
{
    PyObject *m;

    if (PyType_Ready(&PyHashTableType) < 0)
        return NULL;

    m = PyModule_Create(&hashtablemodule);
    if (!m)
        return NULL;

    Py_INCREF(&PyHashTableType);
    PyModule_AddObject(m,
                       "HashTable",
                       (PyObject*)&PyHashTableType);

    return m;
}