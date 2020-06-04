from django import forms

class LoginForm(forms.Form):
    login = forms.CharField(label='Login', max_length=32, required=True)
    password = forms.CharField(label='Password', max_length=32, required=True, widget=forms.PasswordInput())