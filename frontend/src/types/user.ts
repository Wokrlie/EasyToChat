export enum Gender {
  Male,
  Female,
  KeppSecret,
}

export interface User {
  username: string
  nickname: string
  password: string
  gender?: Gender
}
