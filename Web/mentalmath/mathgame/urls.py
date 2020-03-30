from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('play/', views.play, name='play'),
    path('ajax/new_problem', views.new_problem, name='new_problem'),
]
