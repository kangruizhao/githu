from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('add', views.add, name='add'),
    path('addsomething', views.addsomething, name='addsomething'),
    path('editsomething/<foodtype>/<int:_id>', views.editsomething, name='addsomething'),
    path('getdetails', views.getdetails, name='getdetails'),
    path('delete/<foodtype>/<int:_id>/', views.delete, name='delete'),
    path('edit/<foodtype>/<int:_id>/', views.edit, name='edit'),
]
