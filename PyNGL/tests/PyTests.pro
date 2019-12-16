# aux :- Creates a Makefile for not building anything. Use this if no compiler needs to be invoked to create the target; for instance, because your project is written in an interpreted language.
TEMPLATE=aux
TARGET=PyNGLTests
OTHER_FILES+=$$PWD/*.py
CONFIG-=app_bundle
