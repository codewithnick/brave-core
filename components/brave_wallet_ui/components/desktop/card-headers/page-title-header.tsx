// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.
import * as React from 'react'

// styles
import { Row } from '../../shared/style'
import { ButtonIcon, CircleButton, HeaderTitle } from './shared-card-headers.style'

interface Props {
  title: string
  showBackButton?: boolean
  onBack?: () => void
}

export const PageTitleHeader = ({ title, showBackButton, onBack }: Props) => {
  return (
    <Row
      padding='24px 0px'
      justifyContent='flex-start'
    >
      {showBackButton &&
        <CircleButton
          size={28}
          marginRight={16}
          onClick={onBack}
        >
          <ButtonIcon
            size={16}
            name='arrow-left'
          />
        </CircleButton>
      }
      <HeaderTitle>{title}</HeaderTitle>
    </Row>
  )
}
