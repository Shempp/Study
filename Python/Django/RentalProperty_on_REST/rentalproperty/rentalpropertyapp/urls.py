from django.urls import path
from . import views

app_name = 'rentalpropertyapp'
urlpatterns = [
    # ex: /
    path('', views.home, name='rentalproperty-home'),
    # ex: /login
    path('login', views.login, name='rentalproperty-login'),
    # ex: /logout
    path('logout', views.logout, name='rentalproperty-logout'),
]