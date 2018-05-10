import React, { Component } from 'react';
//import './login.css';
import {compose} from "redux"
import { BrowserRouter, Route } from 'react-router-dom';
import '../css/form.css';
import { Link } from 'react-router-dom';
import { connect } from 'react-redux';
//import { Grid, Row, Col } from 'react-bootstrap';
import { Container, Row, Col } from 'reactstrap';
import { reduxForm, Field } from 'redux-form';
import UserField from '../UserField';
import qs from 'qs';
import Login from '../Login';
import axios from 'axios';
import * as actions from '../actions';
const Register=props=>{

  /*  this.state = {
        Username:'',
        Password:''
    }*/
  //  this.handleChange=this.handleChange.bind(this);
  //  this.handleSubmit=this.handleSubmit.bind(this);
  const {handleSubmit}=props ;
  /*  handleChange(e){
      //e.preventDefault();

      this.setState({[e.target.name]: e.target.value}
      ,()=>{
        var userinfo={
          Username:this.state.Username,
          Password:this.state.Password
        }
          console.log(userinfo);
      });


    }
    handleSubmit(e){
      var userinfo={
        Username:this.state.Username,
        Password:this.state.Password
      }
      axios.post('http://localhost:5000', qs.stringify(userinfo));
    }*/

    return (
      <Container>
    	<Row className="row">
			<Col md={{ size: 8, offset: 2 }}>
				<div className="panel panel-login">
        <div className="panel-heading">
						<Row className="row">
							<Col xs="6">
								  <Link to="/" >Login</Link>
							</Col>
							<Col xs="6">
                 <a href="#" className="active" id="login-form-link">Register</a>
							</Col>
						</Row>
						<hr/>
					</div>
      <div className="panel-body">

						<Row className="row">
							<Col lg='12'>
								<form id="login-form" onSubmit={handleSubmit}  role="form"style={{display:'block'}} >
                <Field
             key='Username'
      component={UserField}
      type="text"
      label='Username'
      name='Username'
     />
                <Field
             key='Email'
      component={UserField}
      type="text"
      label='Email'
      name='Email'
     />
     <Field
       key='Password'
       component={UserField}
       type="password"
       label='Password'
       name='Password'
      />

									<br/>
									<div className="form-group">
										<Row >
											<Col md={{ size: 8, offset: 2 }}>
												<button type="submit" name="Submit"  id="login-submit"  className="form-control btn btn-login btn btn-lg btn-primary btn-block">Sign up</button>
											</Col>
										</Row>
									</div>
									<div className="form-group">
										<Row >
											<Col lg="12">
												<div className="text-center">
													<a href="#"  className="forgot-password">Forgot Password?</a>
												</div>
											</Col>
										</Row>
									</div>
								</form>
              </Col>
              </Row>
                </div>
                </div>
              </Col>
              </Row>
                </Container>
    );
  };


export default reduxForm({
    form: 'RegisterForm' // a unique name for this form
})(Register);
