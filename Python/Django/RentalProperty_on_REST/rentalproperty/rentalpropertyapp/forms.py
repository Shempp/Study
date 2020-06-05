from django import forms
from crispy_forms.helper import FormHelper
from crispy_forms.layout import Layout, Submit, Row, Column

class LoginForm(forms.Form):
    login = forms.CharField(label='Имя пользователя:', max_length=32, required=True, widget=forms.TextInput(attrs={'placeholder': 'admin'}))
    password = forms.CharField(label='Пароль:', max_length=32, required=True, widget=forms.PasswordInput())

    # def __init__(self, *args, **kwargs):
    #     super().__init__(*args, **kwargs)
    #     self.helper = FormHelper()
    #     self.helper.layout = Layout(
    #         Row(
    #             Column('login', css_class='form-group col-md-6 mb-0'),
    #             Column('password', css_class='form-group col-md-6 mb-0'),
    #             css_class='form-row'
    #         )
    #     )