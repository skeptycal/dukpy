#include "dukpy.h"


PyTypeObject DukUndefined_Type = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    "Undefined",
    0, 0
};

PyObject DukUndefined = {
  _PyObject_EXTRA_INIT
  1, &DukUndefined_Type
};


static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "dukpy",  /* m_name */
    NULL,       /* m_doc */
    0,          /* m_size */
    NULL,       /* m_methods */
    NULL,       /* m_reload */
    NULL,       /* m_traverse */
    NULL,       /* m_clear */
    NULL        /* m_free */
};

PyObject *PyInit_dukpy(void)
{
    PyObject *mod;

    DukContext_Type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&DukContext_Type) < 0)
        return NULL;

    DukObject_Type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&DukObject_Type) < 0)
        return NULL;

    DukArray_Type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&DukArray_Type) < 0)
        return NULL;

    DukFunction_Type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&DukFunction_Type) < 0)
        return NULL;

    DukEnum_Type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&DukEnum_Type) < 0)
        return NULL;

    mod = PyModule_Create(&moduledef);
    if (mod == NULL)
        return NULL;

    Py_INCREF(&DukContext_Type);
    PyModule_AddObject(mod, "Context", (PyObject *)&DukContext_Type);

    Py_INCREF(Duk_undefined);
    PyModule_AddObject(mod, "undefined", (PyObject *)Duk_undefined);

    return mod;
}
