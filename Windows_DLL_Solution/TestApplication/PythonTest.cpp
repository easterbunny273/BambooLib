#include <Python.h>

#include <iostream>

static PyObject *
spam_system(PyObject *self, PyObject *args)
{
	std::cout << "hello world!" << std::endl;

	Py_IncRef(Py_None);
	return Py_None;
}

static PyMethodDef SpamMethods[] = {
	{"system",  spam_system, METH_VARARGS, "Execute a shell command."},
	{NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spammodule = {
	PyModuleDef_HEAD_INIT,
	"project1",   /* name of module */
	NULL, /* module documentation, may be NULL */
	-1,       /* size of per-interpreter state of the module,
			  or -1 if the module keeps state in global variables. */
	SpamMethods
};

PyMODINIT_FUNC PyInit_Project1(void)
{
	return PyModule_Create(&spammodule);
}